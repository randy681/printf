#include "main.h"

unsigned int neg_width(buffer_t *output, unsigned int printed,
		unsigned char flag, int width);
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flag, int width);
unsigned int string_width(buffer_t *output, unsigned char flag,
		int width, int precision, int size);

/**
* neg_width - stores trailing space to buffer for neg flag
* @output: struct
* @printed: current no of bytes stored already
* @flag: flag mod
* @width: width mod
* Return: no of bytes stored to buffer
*/
unsigned int neg_width(buffer_t *output, unsigned int printed,
		unsigned char flag, int width)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			ret += _memcpy(output, &wid, 1);
	}
	return (ret);
}

/**
* string_width - store lead space to buffer for wid mod
* @output: struct
* @flag: flag
* @width: width
* @precision: prec
* @size: size of string
* Return: no of bytes stored to buffer
*/
unsigned int string_width(buffer_t *output, unsigned char flag,
		int width, int precision, int size)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (precision == -1) ? size : precision;
		for (; width > 0; width--)
			ret += _memcpy(output, &wid, 1);
	}
	return (ret);
}

/**
* print_width: stores space to buffer width mod
* @output: struct
* @printed: no of char printed
* @flag: flag
* @width: width
* Return: no of bytes stored to buffer
*/
unsigned int print_width(buffer_t *output, unsigned int printed,
		 unsigned char flag, int width)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0; )
			ret += _memcpy(output, &wid, 1);
	}
	return (ret);
}
