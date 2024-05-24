#include <stdint.h>
#include <keyboardBuffer.h>
#include <videoDriver.h>

static struct kbuff buff = {0, 0, {'\0'}};
static buffer_ptr ptr = &buff;

void buffer_append(char c) {
    if (buff.pos < BUFFER_LIMIT-1) {
        buff.buffer[buff.pos] = c;
        buff.pos += 1;
        buff.buffer[buff.pos] = 0;
    }
    else{
        buff.pos = 0;
        buff.buffer[buff.pos] = 0;
    }
}

int buffer_len(){
    return buff.len;
}

void setPos(int newPos){
    buff.pos = newPos;
}

void buffer_clear() {
    buff.len = 0;
}

int get_pos() {
    return buff.pos;
}

uint16_t * get_buff() {
    return ptr->buffer;
}

char getBuffAtCurrent() {
    if (buff.pos != 0) {
        return buff.buffer[buff.pos - 1];
    }
    return buff.buffer[BUFFER_LIMIT-1];
}

void consume() {
    if (buff.pos < BUFFER_LIMIT-1) {
        buff.pos += 1;
    } else {
        buff.pos = 0;
    }
}

//void buffer_append(char c) {
//    if (i < BUFFER_LIMIT-1) {
//        kbuff[i++] = c;
//        kbuff[i++] = '\0';
//    }
//}
//
//void buffer_clear() {
//    i = 0;
//    kbuff[i] = '\0';
//}
//
//void buffer_backspace() {
//    if (i > 0) {
//        kbuff[--i] = '\0';
//    }
//}
//
//int get_pos() {
//    return i;
//}
//
//char * get_buff() {
//    return kbuff;
//}
//
//char getBufferAtCurrent() {
//    return kbuff[i];
//}



