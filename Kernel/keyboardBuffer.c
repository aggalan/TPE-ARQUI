#include <stdint.h>
#include <keyboardBuffer.h>
#include <videoDriver.h>
#include "keyboardBuffer.h"
#include "keyboardDriver.h"

static struct kbuff buff = {0, 0, {'\0'}};
static buffer_ptr ptr = &buff;

int buffer_pos = 0;

void buffer_append(char c) {
    if (ptr->pos < BUFFER_LIMIT-1) {
        ptr->buffer[ptr->pos] = c;
        ptr->pos += 1;
        ptr->buffer[ptr->pos] = 0;
    }
    else{
        ptr->pos = 0;
        ptr->buffer[ptr->pos] = 0;
    }
}

int buffer_len(){
    return ptr->len;
}

void setPos(int newPos){
    ptr->pos = newPos;
}

void buffer_clear() {
    ptr->len = 0;
}

int get_pos() {
    return ptr->pos;
}

uint16_t * get_buff() {
    return ptr->buffer;
}

char getBuffAtCurrent() {
    if (ptr->pos != 0) {
        return ptr->buffer[buff.pos - 1];
    }
    return ptr->buffer[BUFFER_LIMIT-1];
}

uint16_t getBuffCharAt(int pos){
    return ptr->buffer[pos];
}

void consume() {
    if (ptr->pos < BUFFER_LIMIT-1) {
        ptr->pos += 1;
    } else {
        ptr->pos = 0;
    }
}
