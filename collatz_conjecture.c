#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * collatz - calculates the collatz conjecture of a positive integer
 *
 * @num: a positive integer
 * Return: the collatz conjecture
 */
int collatz (int num)
{
	printf("%d ", num);
	if (num == 1)
		return (num);
	else
		return (collatz((num % 2 == 0) ? num / 2 : (num * 3) + 1));
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
				printf("The Collatz conjecture of %d is:\n", num);
				collatz(num);
				printf("\n");
			}
		}
	}
	else
	{
		wait(NULL);
	}

	return (0);
}

