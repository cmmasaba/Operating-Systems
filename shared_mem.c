#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

/**
 * shm_write - does the write operation on the shared memory
 *
 * Return: no return value
 */
void shm_write (void)
{
	/* size in bytes of the shared memory object */
	const int SIZE 4096;
	/* name of the shared memory object */
	const char *name = "SH_M";
	/* strings to be written to the shared memory */
	const char *message_1 = "Hello";
	const char *message_2 = "World";
	/* shared memory file descriptor */
	int shm_fd;
	/* pointer to the shared memory */
	void *ptr;

	/* create the shared memory object */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	/* configure te size of the shared memory object */
	ftruncate(shm_fd, SIZE);
	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	/* write to the shaared memory object */
	sprintf(ptr, "%s", message_1);
	ptr += strlen(message_1);
	sprintf(ptr, "%s", message_2);
	ptr += strlen(message_2);
}

/**
 * shm_read - does the read operation from the shared memory
 *
 * Return: no return value
 */
void shm_read (void)
{
	/* size in bytes of the shared memory object */
	const int SIZE 4096;
	/* name of the shared memory object */
	const char *name = "SH_M";
	/* shared memory file descriptor */
	int shm_fd;
	/* pointer to the shared memory */
	void *ptr;

	/* open the file descriptor */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	/* read from the shared memory object */
	printf("%s", (char *)ptr);
	/* remove the shared memory object */
	shm_unlink(name);
}

/**
 * main - the driver program
 *
 * shm_write is done by the process that initiates communication
 * shm_read is done by the process with which communication is desired
 *
 * Return: 0 always successful
 */
int main (void)
{
	shm_write();
	shm_read();

	return (0);
}
