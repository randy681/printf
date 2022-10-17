#include "main.h"

unsigned int _sbase(buffer_t *output, long int num, char *base,
		unsigned char flag, int width, int precision);
unsigned int _ubase(buffer_t *output, unsigned long int num,
		char *base, unsigned char flag, int width, int precision);

/**
* _sbase - convert signed long to input base
* @output: struct
* @num: signed long to be convert
* @base: pointer
* @flag: flag
* @width: width
* @precision: precision
* Return: noof bytes stored to buffer
*/
unsigned int _sbase(buffer_t *output, long int num, char *base,
		unsigned char flag, int width, int precision)
{
	int size;
	char dig;
	char pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;
	if (num >= size || num <= -size)
		ret += _sbase(output, num / size, base, flag, width - 1, precision - 1);
	else
	{
		for (; precision > 1; precision--, width--)
			ret += _memcpy(output, &pad, 1);
		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				ret += _memcpy(output, &pad, 1);
		}
	}
	dig = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &dig, 1);
	return (ret);
}

/**
* _ubase - convert unsigned long to input base
* @output: struct
* @num: long to be converted
* @base: pointer
* @flag: flag
* @width: width
* @precision: prec
* Return: no of bytes stored
*/
unsigned int _ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flag, int width, int precision)
{
	unsigned int size, ret = 1;
	char dig, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;
	if (num >= size)
		ret += _ubase(output, num / size, base, flag, width - 1,
				precision - 1);
	else
	{
		if (((flag >> 5) & 1) == 1)
		{
			width -= 2;
			precision -= 2;
		}
		for (; precision > 1; precision--, width--)
			ret += _memcpy(output, &pad, 1);
		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flag >> 5) & 1) == 1)
			ret += _memcpy(output, lead, 2);
	}
	dig = base[(num % size)];
	_memcpy(output, &dig, 1);
	return (ret);
}
