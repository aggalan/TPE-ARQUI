#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>

void putCh(char c);
char getCh();
int null_or_space(char c);
int null_or_newline(char c);
int strcmp(char * str1, char * str2);
int strcmpspace(char * str1, char * str2);
void print(char * fmt, ...);
void int_to_string(int num, char * buffer);
int strlen(char * str);

#endif