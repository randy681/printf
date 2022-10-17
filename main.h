#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stdint.h>

int _printf(const char *format, ...);

void _vprintf_state_1(const char *format, va_list args);
void putchar_num(long number, int base, char *buffer, int flag);
void putchar_unsigned_num(unsigned long number, int base, char *buffer, int flag);
void putchar_int(int x);
void print_unsigned(unsigned int u, int base, char *buffer, int flag);
int _vprintf(const char *format, va_list args);
int _printf(const char *format, ...);
void _print_by_base(const char *format, va_list args);

#endif /* MAIN_H */
