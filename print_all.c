#include "main.h"

/**
 * putchar_num - prints number
 * @number: number to print
 * @base: base of number to print (e.g., decimal, hexadecimal, octal)
 * @buffer: number buffer
 * @flag: if 1, print hexadecimal numbers in uppercase, otherwise lowercase
 * Return: nothing
 */
void putchar_num(long number, int base, char *buffer, int flag)
{
	char buf[65];
	int i, cur = 0, digit;
	
	if (number < 0)
	{
		*buffer++ = '-';
		number = -number;
	}

	if (number == 0)
	{
		*buffer++ = '0';
		*buffer = 0;
		return;
	}

	for (i = 0; i < 65; i++)
		buf[i] = 0;

	while (number)
	{
		digit = number % base;

		if (digit >= 10 && flag == 1)
			buf[cur++] = 'A' + (digit - 10);
		else if (digit >= 10 && flag == 0)
			buf[cur++] = 'a' + (digit - 10);
		else
			buf[cur++] = '0' + digit;
		number /= base;
	}

	for (i = cur - 1; i != 0; i--)
		*buffer++ = buf[i];

	*buffer++ = buf[0];
	*buffer = 0;
}

/**
 * putchar_int - prints a number
 * @x: number to print
 * Return: nothing
 */
void putchar_int(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}

	if (x / 10)
		putchar_int(x / 10);

	putchar(x % 10 + '0');
}

/**
 * print_unsigned - prints unsigned number
 * @u: unsigned number to print
 * @base: base to print (e.g., decimal, hexadecimal, octal)
 * @buffer: number buffer
 * @flag: if 1, print hexadecimal numbers in uppercase, otherwise lowercase
 */
void print_unsigned(unsigned int u, int base, char *buffer, int flag)
{
	int i;

	putchar_num(u, base, buffer, flag);
	for (i = 0; buffer[i]; i++)
		putchar(buffer[i]);
}

/**
 * _vprintf - prints string and arguments based on format specifiers
 * @format: string to print
 * @args: list of arguments to print
 * Return: length of string
 */
int _vprintf(const char *format, va_list args)
{
	unsigned int state = 0, count = 0;

	while (*format)
	{
		if (state == 0)
		{
			if (*format == '%')
			{
				state = 1;
				count++;
			}
			else
			{
				putchar(*format);
				count++;
			}
		}
		else if (state == 1)
		{
			_vprintf_state_1(format, args);
			state = 0;
		}
		format++;
	}
	return (count);
}

/**
 * _printf - mimicks printf function
 * @format: buffer to print
 * Return: length of buffer
 */
int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;

	va_start(args, format);

	count = _vprintf(format, args);
	va_end(args);

	return (count);
}
