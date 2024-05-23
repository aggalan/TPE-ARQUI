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

int size = 2;

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
    drawchar_color(c, fcolor, 0x00000000);
}

void clear() {
    int i, j;
    for (i = 0; i < 768; i++) {
        for (j = 0; j < 1024; j++) {
            putPixel(0,j, i);
        }
    }
    posX = MARGIN;
    posY = MARGIN;
}

void drawchar_color(char c, uint64_t fcolor, uint64_t bcolor) {
    if (posX >= VBE_mode_info->width-16-MARGIN && posY >= VBE_mode_info->height-32-MARGIN) {
        return;
    }

    if (c == ' ') {
        fcolor = bcolor;
    }else if (c == '\n') {
        newline();
        return;
    }else if (c == '\t') {
        drawWord("  ");
        return;
    }

    int cx, cy;
    int pos = c - 33;
    for (cy = 0; cy < 16; cy++) {
        int maskCheck = 0x01;
        for (cx = 0; cx < 10; cx++) {
            if (((font[(pos*32) + (2*cy)] & (maskCheck << cx)) != 0) && cx < 8) {
                putPixel(fcolor, cx + posX, cy + posY);
            } else {
                putPixel(bcolor, cx + posX, cy + posY);
            }
        }
    }
    if (posX >= VBE_mode_info->width-MARGIN-16) {
        posY += 16;
        posX = MARGIN;
        return;
    }

    posX += 10;


//    for (cy = 0; cy < 16; cy++) {
//        int maskCheck = 0x01;
//        for (cx = 0; cx < 10; cx++) {
//            if (((font[(pos*32) + (2*cy)] & (maskCheck << cx)) != 0) && cx < 8) {
//                putPixel(fcolor, cx*size + posX, cy*size + posY);
//                putPixel(fcolor, cx*size + 1 + posX, cy*size + 1 + posY);
//            }
//            else {
//                putPixel(bcolor, cx*size + posX, cy*size + posY);
//                putPixel(bcolor, cx*size + 1 + posX, cy*size + 1 + posY);
//            }
//        }
//    }
//    if (posX >= VBE_mode_info->width-MARGIN-16) {
//        posY += 16;
//        posX = MARGIN;
//        return;
//    }
//
//    posX += 10*size;

}




void drawWord(char * string) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        drawchar_color(string[i], defaultFColor, defaultBColor);
    }
}

void drawWordColor(char * string, uint64_t fColor, uint64_t bColor){
    for(int i = 0; string[i] != 0; i++){
        drawchar_color(string[i], fColor, bColor);
    }

}

void fill(uint64_t x, uint64_t y, uint64_t color) {

}

void transparent_space() {
    if (posX >= VBE_mode_info->width-10) {
        posY += 16;
        posX = 10;
    } else {
        posX += 10;
    }
}

void tab(){
    drawWord("   ");
 }

void backspace() {
    if (posX == MARGIN && posY == MARGIN) {
        return;
    }
    if (posX <= MARGIN) {
        posX = VBE_mode_info->width-MARGIN-6;
        posY -= 16;
    }
    int i, j;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 10; j++) {
            putPixel(0, posX - j - 1, posY + i);
        }
    }
    posX -= 10;
}

void newline() {
    if (posY >= VBE_mode_info->height-32-MARGIN) {
        return;
    }
    posX = MARGIN;
    posY += 16;
}

void drawWordColorLen(char * string, uint64_t fcolor, uint64_t bcolor, int len){
    for(int i = 0; i < len && string[i] != 0; i++){
        drawchar_color(string[i], fcolor, bcolor );
    }
}

void drawWordLen(char * string, int len){
        for(int i = 0; i < len && string[i] != 0; i++){
        drawchar_color(string[i], defaultFColor, defaultBColor );
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