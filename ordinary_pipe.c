#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 40
#define READ_END 0
#define WRITE_END 1

/**
 * main - a program that illustrates use of ordinary pipes in UNIX
 * ordinary pipes are used for interprocess communication
 *
 * Return: 0 always successful
 */
int main (void)
{
	char write_msg[BUFFER_SIZE] = "Ordinary pipes";
	char read_msg[BUFFER_SIZE];
	int fd[2], len = strlen(write_msg);
	pid_t pid;

	/* create the pipe using the pipe() syscall */
	if (pipe(fd) == -1)
	{
		fprintf(stderr, "Failed to create pipe.\n");
		return (-1);
	}

	/* create a new process */
	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Failed to create a child process.\n");
		return (-1);
	}
	else if (pid > 0) /* parent process */
	{
		/* close the unused end of the pipe */
		close(fd[READ_END]);
		/* write to the pipe */
		write(fd[WRITE_END], write_msg, len);
		/* close the write end when done */
		close(fd[WRITE_END]);
	}
	else /* child process */
	{
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);
		/* read from the pipe */
		read(fd[READ_END], read_msg, len);
		printf("Read: %s\n", read_msg);
		/* close the read end when done */
		close(fd[READ_END]);
	}

	return (0);
}
