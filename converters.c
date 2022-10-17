#include "main.h"

unsigned int _char(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _perc(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _string(va_list ap, buffer_t *output, unsigned char flag,
		 int width, int precision, unsigned char len);
unsigned int _int (va_list ap, buffer_t *output, unsigned char flag,
		 int width, int precision, unsigned char len);
unsigned int _bin(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);

/**
 * _char - converts tounsigned char and stores in buffer
 * @ap: arg
 * @output: struct
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: no.of bytes stored in buffer
 */

unsigned int _char(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	char c;
	unsigned int ret = 0;

	(void)precision;
	(void)len;
	c = va_arg(ap, int);
	ret += print_width(output, ret, flag, width);
	ret += _memcpy(output, &c, 1);
	ret += neg_width(output, ret, flag, width);

	return (ret);
}

/**
 * _perc - stored % to buffer
 * @ap: arg
 * @output: struct
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 * Return: no . of bytes stored tobuffer
 */

unsigned int _perc(va_list ap, buffer_t *output, unsigned char flag,
		 int width, int precision, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)ap;
	(void)precision;
	(void)len;

	ret += print_width(output, ret, flag, width);
	ret += _memcpy(output, &percent, 1);
	ret += neg_width(output, ret, flag, width);

	return (ret);
}

/**
 * _string - convertes arg to string and stores in buffer
 * @ap: arg
 * @output: buffer struct
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: no. ofbytes
 */

unsigned int _string(va_list ap, buffer_t *output, unsigned char flag,
		 int width, int precision, unsigned char len)
{
	char *str;
	char *null = "(null)";
	int size;
	unsigned int ret = 0;

	(void)flag;
	(void)len;
	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0 ; *(str + size) ; )
		size++;
	ret += string_width(output, flag, width, precision, size);
	precision = (precision == -1) ? size : precision;
	while (*str != '\0')
	{
		ret += _memcpy(output, str, 1);
		precision--;
		str++;
	}
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
 * _int - converts to signed int and stores in buffer
 * @ap: arg
 * @output: struct
 * @flag: flag
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: bytes stored
 */

unsigned int _int(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		d = va_arg(ap, long int);
	else
		d = va_arg(ap, int);
	if (len == SHORT)
		d = (short)d;
	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(output, &space, 1);
	if (precision <= 0 && NEG_FLAG == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		if  (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
			ret += _memcpy(output, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);
	if (!(d == 0 && precision == 0))
		ret += _sbase(output, d, "0123456789", flag, 0, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
* _bin - converts unsigned int to binary
* @ap: arg
* @flag: flag
* @width: width
* @precision: prec
* @len: length
* @output: struct
* Return: no of bytes stored
*/
unsigned int _bin(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	unsigned int num = va_arg(ap, unsigned int);

	(void)len;
	return (_ubase(output, num, "01", flag, width, precision));
}
