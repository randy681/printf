#include "main.h"

unsigned int _dec(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _oct(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int lower_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int upper_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);

/**
 * _dec - converts unsign int to dec and stores in buffer
 * @ap: arg
 * @output: struct
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: no of bytes stored to buffer
 */

unsigned int _dec(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (!(num == 0 && precision == 0))
		ret += _ubase(output, num, "0123456789", flag,
				width, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
 * _oct - conv unsignedint to oct and stores in buffer
 * @output: struct
 * @ap: arg
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: no of bytes stored
 */

unsigned int _oct(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, &zero, 1);
	if (!(num == 0 && precision == 0))
		ret += _ubase(output, num, "01234567", flag, width, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
 * lower_hex - conv usigned int to hex and stores to buffer
 * @output: struct
 * @ap: arg
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: noof bytes stoed
 */

unsigned int lower_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(ap, unsigned long int);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);
	if (!(num == 0 && precision  == 0))
		ret += _ubase(output, num, "0123456789abcdef", flag, width, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
 * upper_hex - converts unsigned int to hex
 * @output: struct
 * @ap: arg
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: no of bytes stored to buffer
 */

unsigned int upper_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(ap, unsigned long);
	else
		num = va_arg(ap, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;
	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);
	if (!(num == 0 && precision == 0))
		ret += _ubase(output, num, "0123456789ABCDEF", flag,
				width, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}
