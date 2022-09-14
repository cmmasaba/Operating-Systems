#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * copy - copies the contents of the source file to the destination file
 * @src: pathname of the source file
 * @dest: pathname of the second file
 *
 * Return: the number of bytes that were copied; or -1 if the copy failed
 */
ssize_t copy (const char src[], const char dest[])
{
	int fd1, fd2;
	int nchars = 0, w = 0, r = 0;
	int fsync1, fsync2, close1, close2;	
	char buffer[81];

	/* check if source file exists */
	if (!src)
	{
		printf("Source file not found!!!\n");
		return (-1);
	}

	fd1 = open(src, O_RDONLY);
	fd2 = open(dest, O_CREAT | O_WRONLY, 0764);
	/* confirm the open operations for both files were successful */
	if (fd1 == -1)
	{
		printf("Unable to open the source file!!!\n");
		return (-1);
	}
	if (fd2 == -1)
	{
		printf("Unable to open the destination file!!!\n");
		return (-1);
	}

	/* the read and write operation */
	while( (r = read(fd1, buffer, 80)) > 0)
	{
		w = write(fd2, buffer, r);
		/* check if the write operation was successful */
		if (w == -1)
		{
			printf("Error writing to file!!!\n");
			return (-1);
		}
		nchars += w;
	}

	/* precede the close operations with fsync */
	fsync1 = fsync(fd1);
	fsync2 = fsync(fd2);
	close1 = close(fd1);
	close2 = close(fd2);
	/* check if the files were properly closed */
	if ( (fsync1 == 1) || (fsync2 == -1))
	{
		if ( (close1 == -1) || (close2 == -1))
		{
			printf("Failed to close the file descriptors for the\
				source and destination files.\n Possible I/O\
				leaks may occur.\n");
		}
	}

	return (nchars);
}

/**
 * main - driver program
 * asks the user to enter the name of the source file and the destination file
 *
 * Return: 0 always success
 */
int main (void)
{
	char src[81], dest[81];
	ssize_t status;

	printf("Enter the name of the source file: ");
	scanf("%80s", src);
	printf("Enter the name of the destination file: ");
	scanf("%80s", dest);

	status = copy(src, dest);
	if (status != -1)
		printf("Copied successfuly.\n");
	else
		printf("Unable to copy!!!\n");

	return (0);
}
