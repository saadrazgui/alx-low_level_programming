#include "main.h"

void cant_close(int fd);
void cant_write(char *file_to);
void cant_read(char *file_from);

/**
 * main - afunction to cp one file into another
 * @argc: the number of args we will be passed
 * @argv: an array of arguments
 * Return: 0 for success
 */

int main(int argc, char *argv[])
{
	int fd1, fd2;
	ssize_t rd, wrt;
	char *buf[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	if (argv[1] == NULL)
		cant_read(argv[1]);

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		cant_read(argv[1]);

	fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd2 == -1)
		cant_write(argv[2]);

	rd = read(fd1, buf, 1024);
	if (rd == -1)
		cant_read(argv[1]);
	wrt = write(fd2, buf, rd);
	if (wrt == -1)
		cant_write(argv[2]);

	while (rd == 1024)
	{
		rd = read(fd1, buf, 1024);
		if (rd == -1)
			cant_read(argv[1]);

		wrt = write(fd2, buf, rd);
		if (wrt == -1)
			cant_write(argv[2]);
	}

	if (close(fd1) < 0)
		cant_close(fd1);
	if (close(fd2) < 0)
		cant_close(fd2);

	return (0);
}
/**
 * cant_read - a function to print an error and exit
 * @file_from: a pointer to our originalfile
 */
void cant_read(char *file_from)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
	exit(98);
}
/**
 * cant_write - a function to print an error message and exit
 * @file_to: a pointer to our receiving file
 */
void cant_write(char *file_to)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
	exit(99);
}

/**
 * cant_close - a function to print out an error and exit
 * @fd: our file descriptor
 */
void cant_close(int fd)
{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
	exit(100);
}
