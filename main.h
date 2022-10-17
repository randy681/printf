#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* flag macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flag & 1)
#define SPACE_FLAG ((flag >> 1) & 1)
#define HASH_FLAG ((flag >> 2) & 1)
#define ZERO_FLAG ((flag >> 3) & 1)
#define NEG_FLAG ((flag >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2


 /**
 * struct buffer_s - type def buffer struct
 * @buffer: char array pointer
 * @start: start buffer pointer
 * @len: length
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct flag_s - typr def for flags struct
 * @flag: char repflag
 * @value: intvalof flag
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;
/**
 * struct converter_s - type def for coverter struct
 * @spec: conv spec char
 * @func: pointer to conv fn
 */
typedef struct converter_s
{
	unsigned char spec;
	unsigned int (*func)(va_list, buffer_t *, unsigned char,
			int, int, unsigned char);
} converter_t;

/*specifier fn*/
unsigned int _char(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _string(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _perc(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _int(va_list ap, buffer_t *output, unsigned char flags,
		int width, int precision, unsigned char len);
unsigned int _bin(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _dec(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _oct(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int lower_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int upper_hex(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _S(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _p(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _r(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _R(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);

/* handler */
unsigned char _flag(const char *flag, char *i);
unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);
unsigned char _length(const char *modifier, char *i);
int _width(va_list ap, const char *modifier, char *i);
int _precision(va_list ap, const char *modifier, char *i);


/* modifier */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flag, int width);
unsigned int string_width(buffer_t *output, unsigned char flag,
		int width, int precision, int size);
unsigned int neg_width(buffer_t *output, unsigned int printed,
		unsigned char flag, int width);

/* helper fn */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int _sbase(buffer_t *output, long int num, char *base,
		 unsigned char flag, int width, int precision);
unsigned int _ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flag, int width, int precision);

int _printf(const char *format, ...);

#endif
