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
void call_cursor_on();
void call_cursor_off();
void call_sound(int time, int frequency);
void call_paint_screen(uint64_t color);
void call_drawWordColorAt(char * string, uint64_t color, uint32_t x, uint32_t y);
void call_put_square(uint64_t x, uint64_t y, uint32_t size, uint64_t color);
void call_sleepms(int ms);
void call_sleeps(int s);
uint64_t call_pixelColorAt(uint64_t x, uint64_t y);
#endif