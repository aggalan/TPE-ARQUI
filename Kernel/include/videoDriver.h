#ifndef VIDEO_DRIVER_H 
#define VIDEO_DRIVER_H 
#include <stdint.h>
void putPixel(uint64_t hexColor, uint64_t x, uint64_t y);
void drawchar_transparent(char c, uint64_t fcolor);
void drawchar_color(char c, uint64_t fcolor, uint64_t bcolor);
void drawWordColor(char * string, uint64_t fColor, uint64_t bColor);
void drawWord(char * string);
void fill(uint64_t x, uint64_t y, uint64_t color);
void fillPos(int size, uint64_t color);
void backspace();
void newline();
void clear();
void tab();
void drawWordLen(char * string, int len);
void drawWordColorLen(char * string, uint64_t fcolor, uint64_t bcolor, int len);
void invalidFD();
void drawRegister(int valueReg);
void clearColor(uint64_t color);

#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define MARGIN 10
#endif