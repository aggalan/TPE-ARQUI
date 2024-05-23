#ifndef _KEYBOARD_BUFFER_
#define _KEYBOARD_BUFFER_
#include <stdint.h>

#define BUFFER_LIMIT 256


struct kbuff {
    int pos;
    int len;
    uint16_t buffer[BUFFER_LIMIT];
};

typedef struct kbuff * buffer_ptr;

void buffer_append(char c);
void buffer_clear();
void buffer_backspace();
int get_pos();
uint16_t * get_buff();
char getBuffAtCurrent();
void consume_char();
int buffer_len();
void setPos(int newPos);


#endif