#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

/**
 * main - the driver program
 * copies the contents of the source file to the destination file
 * the source file and destination file are provided on the cmd as arguments
 *
 * @argc: the number of arguments provided
 * @argv: the arguments given to the program
 *
 * Return: 0 always success
 */
int main (int argc, char *argv[])
{
	int fd[2], fd1, fd2;
	int rchars;
	char buffer[256];
	pid_t pid;

	if (argc < 3)
	{
		printf("Few arguments provided.\n");
		printf("Usage: copy [source_file] [destination_file]\n");
		return (-1);
	}
	else if (argc > 3)
	{
		printf("Too many arguments provided.\n");
		printf("Usage: copy [source_file] [destination_file]\n");
		return (-1);
	}
	else if (!argv[1])
	{
		printf("The source file does not exist in the system.\n");
		return (-1);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return (-1);
		}

		fd1 = open(argv[1], O_RDWR);
		fd2 = open(argv[2], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (fd1 < 0 || fd2 < 0)
		{
			perror("open");
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
			close(fd[READ]);
			while ((rchars = read(fd1, buffer, 255)) > 0)
			{
				write(fd[WRITE], buffer, rchars);
			}
			close(fd[WRITE]);
			close(fd1);
		}
		else
		{
			close(fd[WRITE]);
			while((rchars = read(fd[READ], buffer, 255)) > 0)
			{
				write(fd2, buffer, rchars);
			}
			close(fd[READ]);
			close(fd2);
		}
	}

	close(fd1);
	close(fd2);
	return (0);
}
