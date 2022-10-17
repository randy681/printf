#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
void free_buffer(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - copies n bytes fromsrc to buffer
 * @output: struct
 * @src: pointer
 * @n: number of bytes
 *
 * Return: bytes copied
 */

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0 ; i < n ; i++)
	{
		*(output->buffer) = *(src + i);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}
		else
			(output->buffer)++;
	}
	return (n);
}

/**
 * free_buffer - frees struct buffer
 * @output: buffer to be freed
 */

void free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - initializes buffer_t
 *
 * Return: pointer to buffer_t
 */

buffer_t *init_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;
	return (output);
}
