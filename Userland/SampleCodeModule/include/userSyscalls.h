#include <stdint.h>

#ifndef USERSYSCALLS_H
#define USERSYSCALLS_H

#define STDOUT 1
#define STDERR 2
#define STDIN 0

void putC(char * buff, int size, int fd);
void getC(char * buff, int size, int fd);
#endif