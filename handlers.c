#include "main.h"

unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);
unsigned char _flag(const char *flag, char *i);
unsigned char _length(const char *modifier, char *i);
int _width(va_list ap, const char *modifier, char *i);
int _precision(va_list ap, const char *modifier, char *i);

/**
* _length - matches length mod with corr value
* @modifier: pointer
* @i: index counter
* Return: corr value or 0
*/
unsigned char _length(const char *modifier, char *i)
{
	if (*modifier == 'h')
	{
		(*i)++;
		return (SHORT);
	}
	else if (*modifier == 'l')
	{
		(*i)++;
		return (LONG);
	}
	return (0);
}

/**
* _width - matches width mod with corr value
* @ap: arg
* @modifier: pointer
* @i: index counter
* Return: value or 0
*/
int _width(va_list ap, const char *modifier, char *i)
{
	int val = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*i)++;
		if (*modifier == '*')
		{
			val = va_arg(ap, int);
			if (val <= 0)
				return (0);
			return (val);
		}
		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}
	return (val);
}

/**
* _precision - matches prec mod with corr val
* @ap: arg
* @modifier: pointer
* @i: index counter
* Return: value or 0
*/
int _precision(va_list ap, const char *modifier, char *i)
{
	int val = 0;

	if (*modifier != '.')
		return (-1);
	modifier++;
	(*i)++;
	if ((*modifier <= '0' || *modifier > '9') &&
			*modifier != '*')
	{
		if (*modifier == '0')
			(*i)++;
		return (0);
	}
	while ((*modifier >= '0' && *modifier <= '9') ||
			(*modifier == '*'))
	{
		(*i)++;
		if (*modifier == '*')
		{
			val = va_arg(ap, int);
			if (val <= 0)
				return (0);
			return (val);
		}
		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}
	return (val);
}
/**
 * _flag - match flag with corresponding val
 * @flag: pointer
 * @i: counter fororig format str
 *
 * Return: corresponding val
 */

unsigned char _flag(const char *flag, char *i)
{
	int j, k;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{'-', NEG},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{0, 0}
	};

	for (j = 0 ; flag[j] ; j++)
	{
		for (k = 0 ; flags[k].flag != 0 ; k++)
		{
			if (flag[j] == flags[k].flag)
			{
				(*i)++;
				if (ret == 0)
					ret = flags[k].value;
				else
					ret |= flags[k].value;
				break;
			}
		}
		if (flags[k].value == 0)
			break;
	}
	return (ret);
}


/**
 * _specifiers - match conversion spec to conversion fn
 * @spec: pointer to conv spec
 *
 * Return: pointer to fn or NULL
 */

unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t conv[] = {
		{'c', _char},
		{'s', _string},
		{'%', _perc},
		{'d', _int},
		{'i', _int},
		{'b', _bin},
		{'u', _dec},
		{'o', _oct},
		{'x', lower_hex},
		{'X', upper_hex},
		{'S', _S},
		{'p', _p},
		{'r', _r},
		{'R', _R},
		{0, NULL}
	};

	for (i = 0 ; conv[i].func ; i++)
	{
		if (conv[i].spec == *spec)
			return (conv[i].func);
	}
	return (NULL);
}

