#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

/**
 * reverse - changes the alphabetic case of a each letter in string passed to it
 * @str: the string given as argument
 *
 * Return: no return value
 */

void reverse (char *str)
{
	int i;

	while (*str != '\0')
	{
		if (*str >= 97 && *str <= 122)
		{
			for (i = 97; i <= 122; ++i)
				if (*str == i)
					*str = i - 32;
		}
		else
		{
			for (i = 65; i <= 90; ++i)
				if (*str == i)
					*str = i + 32;
		}
		++str;
	}
}

/**
 * main - the driver program
 *
 * the parent process creates a child process and sends a string mrssage ti it
 * using ordinary pipes.
 * The child process reverses the cases in the string message and sends the new
 * string back to the parent process
 *
 * Return: 0 Always success
 */
int main (void)
{
	char *message, *read_msg;
	int fd1[2], fd2[2], len;
	size_t i = 0;
	pid_t pid;

	read_msg = malloc(sizeof(char) * 256);
	if (!read_msg)
	{
		perror("malloc");
		return (-1);
	}

	printf("Enter a string: \n");
	len = getline(&message, &i, stdin);

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		perror("pipe");
		return (-1);
	}

	pid = fork();

	if (pid < 0)
	{
		perror("pid");
		return (-1);
	}
	else if (pid > 0)
	{
		close(fd1[READ_END]);
		write(fd1[WRITE_END], message, len);
		close(fd1[WRITE_END]);
		wait(NULL);
		close(fd2[WRITE_END]);
		read(fd2[READ_END], message, len);
		close(fd2[READ_END]);
		printf("The string with reversed cases is:\n%s\n", message);
	}
	else
	{
		close(fd1[WRITE_END]);
		read(fd1[READ_END], read_msg, len);
		close(fd1[READ_END]);
		reverse(read_msg);
		close(fd2[READ_END]);
		write(fd2[WRITE_END], read_msg, len);
		close(fd2[WRITE_END]);
	}

	free(message);
	free(read_msg);
	return (0);
}
