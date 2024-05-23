#include <stdint.h>

#ifndef USERSYSCALLS_H
#define USERSYSCALLS_H

#define STDOUT 1
#define STDERR 2
#define STDIN 0

void call_sys_read(char *buf, int size, int fd);
void call_sys_write(char *buf, int size, int fd);
void call_timeClock(char *buf);
void call_regState();
void call_clear();
void call_size_up();
void call_size_down();
void call_font();
#endif