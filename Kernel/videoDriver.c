#include <videoDriver.h>
#include <stdint.h>
#include <keyboardBuffer.h>
#include <keyboardDriver.h>
#include <font.h>
#include "naiveConsole.h"


struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

uint32_t posX = MARGIN;
uint32_t posY = MARGIN;

int size = DEFAULT_FONT_SIZE;

uint64_t defaultFColor = WHITE;
uint64_t defaultBColor = BLACK;

void putPixel(uint64_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void drawchar_transparent(char c, uint64_t fcolor) {
    drawchar_color(c, fcolor, BLACK);
}

void clear() {
    int i, j;
    for (i = 0; i < VBE_mode_info->height; i++) {
        for (j = 0; j < VBE_mode_info->width; j++) {
            putPixel(0,j, i);
        }
    }
    posX = MARGIN;
    posY = MARGIN;
}

void drawchar_color(char c, uint64_t fcolor, uint64_t bcolor) {
    cursorOff();
    if (posX >= VBE_mode_info->width-(16*size)-MARGIN && posY >= VBE_mode_info->height-(32*size)-MARGIN) {
        move_screen();
    }

    if (c == ' ') {
        fcolor = bcolor;
    }

    int cx, cy;
    int pos = c - 33;
    if(isMinusc(c)){
        pos = c - 'a';
    }
//    for (cy = 0; cy < 16; cy++) {
//        int maskCheck = 0x01;
//        for (cx = 0; cx < 10; cx++) {
//            if (((font[(pos*32) + (2*cy)] & (maskCheck << cx)) != 0) && cx < 8) {
//                putPixel(fcolor, cx + posX, cy + posY);
//            } else {
//                putPixel(bcolor, cx + posX, cy + posY);
//            }
//        }
//    }
//    if (posX >= VBE_mode_info->width-MARGIN-16) {
//        posY += 16;
//        posX = MARGIN;
//        return;
//    }
//
//    posX += 10;


    for (cy = 0; cy < 16; cy++) {
        int maskCheck = 0x01;
        for (cx = 0; cx < 10; cx++) {
            if (((font[(pos*32) + (2*cy)] & (maskCheck << cx)) != 0) && cx < 8) {

                for (int z = 0; z < size; z++) {
                    putPixel(fcolor, cx*size + posX + z, cy*size + posY);
                }

            }
            else {

                for (int w = 0; w < size; w++) {
                    putPixel(bcolor, cx*size + posX + w, cy*size + posY);
                }

            }
        }
    }
    if (posX >= VBE_mode_info->width-MARGIN-(16*size)) {
        posY += 16*size;
        posX = MARGIN;
        return;
    }

    posX += 10*size;

}

void put_square(uint64_t x, uint64_t y, uint32_t size, uint64_t color) {
    for (uint32_t i = 0; i < size; i++) {
        for (uint32_t j = 0; j < size; j++) {
            putPixel(color, x + j, y + i);
        }
    }
}


void character(char character, uint64_t fcolor, uint64_t bcolor){
    if(character == '\b'){
        backspace();
        return;
    }
    if(character == '\n'){
        newline();
        return;
    }
    if(character == '\t'){
        tab();
        return;
    }
    if (character == 0x7C) {
        moveLeft();
        return;
    }
//    if (character == 0x7D) {
//        moveRight();
//        return;
//    }

    drawchar_color(character, fcolor, bcolor);
    return;
}

void drawWord(char * string) {
    drawWordColor(string, defaultFColor, defaultBColor);
}

void drawWordColorAt(char * string, uint64_t color, uint32_t x, uint32_t y){
    uint32_t px = posX;
    uint32_t py = posY;
    posX = x;
    posY = y;
    drawWordColor(string, color, defaultBColor);
    posX = px;
    posY = py;
}

void drawWordAt(char * string, uint32_t x, uint32_t y){ 
    drawWordColorAt(string, defaultFColor, x, y);
}


void drawWordColor(char * string, uint64_t fColor, uint64_t bColor){
    for(int i = 0; string[i] != 0; i++){
        character(string[i], fColor, bColor);
    }

}

// void fill(uint64_t x, uint64_t y, uint64_t color) {

// }

void transparent_space() {
    if (posX >= VBE_mode_info->width-(10*size)) {
        posY += 16*size;
        posX = MARGIN + 10*size;
    } else {
        posX += 10*size;
    }
}

void drawChar(char c){
    character(c, defaultFColor, defaultBColor);
}

void tab(){
    drawWord("  ");
 }

void backspace() {
    if (posX == MARGIN && posY == MARGIN) {
        return;
    }
    cursorOff();
    if (posX <= MARGIN) {
        posX = VBE_mode_info->width-MARGIN-(6*size);
        posY -= 16*size;
    }
    int i, j;
    for (i = 0; i < 16*size; i++) {
        for (j = 0; j < 10*size; j++) {
            putPixel(0, posX - j - 1, posY + i);
        }
    }


    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;

    for (int i = posY; i < VBE_mode_info->height + 16; i++) {
        for (int j = posX; j < VBE_mode_info->width; j++) {

            uint64_t offset = (j * ((VBE_mode_info->bpp)/8)) + (i * VBE_mode_info->pitch);

            uint8_t blue = framebuffer[offset];
            uint8_t green = framebuffer[offset + 1];
            uint8_t red = framebuffer[offset + 2];

            uint64_t hexColor = (red << 16) | (green << 8) | blue;

            putPixel(hexColor, j - (10*size), i);


        }
    } // hacer esto mas eficiente comparando si esta bien o en el medio de palabra


    posX -= 10*size;
}

void newline() {
    cursorOff();
    if (posY >= VBE_mode_info->height-(32*size)-MARGIN) {
        move_screen();
    }
    posX = MARGIN;
    posY += 16*size;
}

void drawWordColorLen(char * string, uint64_t fcolor, uint64_t bcolor, int len){
    for(int i = 0; i < len && string[i] != 0; i++){
        character(string[i], fcolor, bcolor );
    }
}

void drawWordLen(char * string, int len){
        for(int i = 0; i < len && string[i] != 0; i++){
        character(string[i], defaultFColor, defaultBColor );
    }
}

void invalidFD(){
    drawWordColor("Invalid File Descriptor entered", WHITE, RED);
}

void drawRegister(int valueReg){
    char buff[256] = {0};
    uintToBase(valueReg, buff, 16);
    drawWordColor(buff, WHITE, BLACK);
    newline();
}


void clearColor(uint64_t color){
        int i, j;
    for (i = 0; i < VBE_mode_info->height; i++) {
        for (j = 0; j < VBE_mode_info->width; j++) {
            putPixel(color,j, i);
        }
    }
    posX = MARGIN;
    posY = MARGIN;

}

void move_screen() {
    posY -= 16*size;

    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;

    for (int i = MARGIN + (16*size); i < VBE_mode_info->height + 16; i++) {
        for (int j = MARGIN; j < VBE_mode_info->width; j++) {

            uint64_t offset = (j * ((VBE_mode_info->bpp)/8)) + (i * VBE_mode_info->pitch);

            uint8_t blue = framebuffer[offset];
            uint8_t green = framebuffer[offset + 1];
            uint8_t red = framebuffer[offset + 2];

            uint64_t hexColor = (red << 16) | (green << 8) | blue;

            putPixel(hexColor, j, i- (16*size) - size );


        }
    }
}

void size_up(){
    if(size == 3){
        drawWordColor("ERROR - Font size already at 3\n", WHITE, RED);
        return;
    }else{
        size++;
        clear();
    }

    return;
}

void size_down(){
    if(size == 1){
        drawWordColor("ERROR - Font size already at 1\n", WHITE, RED);
        return;
    }else{
        size--;
        clear();
    }
    return;
}
void fontSize() {
    char sizeStr[12];  
    intToStr(size, sizeStr, 10);  

    drawWordColor("Size of font is ", WHITE, BLACK);
    drawWord(sizeStr);
    drawChar('\n');
}

void intToStr(int value, char* str, int base) {
    char* ptr = str;
    char* ptr1 = str;
    char tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789"[tmp_value - value * base];
    } while (value);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

void cursorOff() {
    for (int i = 0; i < 10; i++) {
        for (int z = 0; z < size; z++) {
            putPixel(0x00000000, i*size + posX + z, posY + 16*size - 1);
        }
    };
}

void cursorOn() {
    for (int i = 0; i < 10; i++) {
        for (int z = 0; z < size; z++) {
            putPixel(0x00FFFFFF, i*size + posX + z, posY + 16*size - 1);
        }
    }
}

void moveLeft() {
    cursorOff();
    if (posX <= MARGIN) {
        posX = VBE_mode_info->width - MARGIN - (6 * size);
        posY -= 16 * size;
    }
    posX -= 10*size;
}

void moveRight() {
    cursorOff();
    if (posX >= VBE_mode_info->width - MARGIN) {
        posX = MARGIN;
        posY += 16 * size;
    }
    posX += 10*size;
}
