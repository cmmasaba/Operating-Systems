#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

/**
 * collatz - calculates the collatz conjecture of a positive integer
 *
 * @num: a positive integer
 * Return: the collatz conjecture
 */
int collatz (int num)
{
	const int size = 4096; /* the size of the shared memory location */
	const char *name = "collatz"; /* the name of the shared memory location */
	int shm_fd; /* file descriptor of the shared memory */
	void *ptr; /* ponter used to refer to the shared memory */
	int len;

	/* opening the file descripto with read/write permission */
	shm_fd = shm_open(name, O_RDWR, 0666);
	/* memory mapping the shared memory location */
	ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	while (num)
	{
		len = snprintf(NULL, 0, "%d", num);
		/* write the string to the shared memory and advance th pointer forward */
		sprintf(ptr, "%d ", num);
		ptr += len + 1;
		if (num == 1)
			break;
		else
		{
			if (num % 2 == 0)
				num = num / 2;
			else
				num = (num * 3) + 1;
		}
	}
	
	return (0);
}

/**
 * main - the driver program
 * @argc: the number of arguments passed to the program
 * @argv: the arguments passed to the function.
 * The positive integer is passed along on the command line
 *
 * the parent process creates a child process using fork
 * inside the child process, the collatz conjecture is generated
 * and the output is printed to the screen
 *
 * Return: 0 always success
 */
int main (int argc, char **argv)
{
	pid_t pid;
	int num;
	int collatz (int num);
	const int size = 4096;
	const char *name = "collatz";
	int shm_fd;
	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, size);
	ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (argc == 1)
		{
			printf("Insufficient arguments provided.\n");
			printf("Usage: collatz [positive integer]\n");
			return (-1);
		}
		else if (argc > 2)
		{
			printf("Too many arguments provided.\n");
			printf("Usage: collatz [positive integer]\n");
			return (-1);
		}
		else
		{
			num = atoi(argv[1]);
			if (num <= 0)
			{
				printf("Provide a positive integer greater than 0\n");
				return (-1);
			}
			else
			{
				collatz(num);
			}
		}
	}
	else
	{
		wait(NULL);
		num = atoi(argv[1]);
		printf("The Collatz conjecture of %d is:\n", num);
		printf("%s\n", (char *)ptr);
		shm_unlink(name);
	}

	return (0);
}

