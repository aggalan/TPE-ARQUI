#ifndef _ELIMINATOR_H_
#define _ELIMINATOR_H_

void start_game();


#define NUM_KEYS 128

typedef struct {
    unsigned char make;
    unsigned char break_code;
} KeyCode;

static KeyCode ScanCodes[NUM_KEYS] = {
        {0, 0},       // 0x00
        {0x1B, 0x81}, // 0x01 Esc
        {'1', 0x82},  // 0x02 1
        {'2', 0x83},  // 0x03 2
        {'3', 0x84},  // 0x04 3
        {'4', 0x85},  // 0x05 4
        {'5', 0x86},  // 0x06 5
        {'6', 0x87},  // 0x07 6
        {'7', 0x88},  // 0x08 7
        {'8', 0x89},  // 0x09 8
        {'9', 0x8A},  // 0x0A 9
        {'0', 0x8B},  // 0x0B 0
        {'-', 0x8C},  // 0x0C -
        {'=', 0x8D},  // 0x0D =
        {'\b', 0x8E}, // 0x0E Backspace
        {'\t', 0x8F}, // 0x0F Tab
        {'q', 0x90},  // 0x10 q
        {'w', 0x91},  // 0x11 w
        {'e', 0x92},  // 0x12 e
        {'r', 0x93},  // 0x13 r
        {'t', 0x94},  // 0x14 t
        {'y', 0x95},  // 0x15 y
        {'u', 0x96},  // 0x16 u
        {'i', 0x97},  // 0x17 i
        {'o', 0x98},  // 0x18 o
        {'p', 0x99},  // 0x19 p
        {'[', 0x9A},  // 0x1A [
        {']', 0x9B},  // 0x1B ]
        {'\n', 0x9C}, // 0x1C Enter
        {0x00, 0x9D}, // 0x1D Left Ctrl
        {'a', 0x9E},  // 0x1E a
        {'s', 0x9F},  // 0x1F s
        {'d', 0xA0},  // 0x20 d
        {'f', 0xA1},  // 0x21 f
        {'g', 0xA2},  // 0x22 g
        {'h', 0xA3},  // 0x23 h
        {'j', 0xA4},  // 0x24 j
        {'k', 0xA5},  // 0x25 k
        {'l', 0xA6},  // 0x26 l
        {';', 0xA7},  // 0x27 ;
        {'\'', 0xA8}, // 0x28 '
        {'`', 0xA9},  // 0x29 `
        {0x2A, 0xAA}, // 0x2A Left Shift
        {'\\', 0xAB}, // 0x2B '\'
        {'z', 0xAC},  // 0x2C z
        {'x', 0xAD},  // 0x2D x
        {'c', 0xAE},  // 0x2E c
        {'v', 0xAF},  // 0x2F v
        {'b', 0xB0},  // 0x30 b
        {'n', 0xB1},  // 0x31 n
        {'m', 0xB2},  // 0x32 m
        {',', 0xB3},  // 0x33 ,
        {'.', 0xB4},  // 0x34 .
        {'/', 0xB5},  // 0x35 /
        {0x36, 0xB6}, // 0x36 Right Shift
        {'*', 0xB7},  // 0x37 Keypad *
        {0x00, 0xB8}, // 0x38 Left Alt
        {' ', 0xB9},  // 0x39 Space
        {0x00, 0xBA}, // 0x3A Caps Lock
        {0x00, 0xBB}, // 0x3B F1
        {0x00, 0xBC}, // 0x3C F2
        {0x00, 0xBD}, // 0x3D F3
        {0x00, 0xBE}, // 0x3E F4
        {0x00, 0xBF}, // 0x3F F5
        {0x00, 0xC0}, // 0x40 F6
        {0x00, 0xC1}, // 0x41 F7
        {0x00, 0xC2}, // 0x42 F8
        {0x00, 0xC3}, // 0x43 F9
        {0x00, 0xC4}, // 0x44 F10
        {0x00, 0xC5}, // 0x45 Num Lock
        {0x00, 0xC6}, // 0x46 Scroll Lock
        {'7', 0xC7},  // 0x47 Keypad 7
        {0x7B, 0xC8},  // 0x48 Keypad 8
        {'9', 0xC9},  // 0x49 Keypad 9
        {'-', 0xCA},  // 0x4A Keypad -
        {0x7C, 0xCB},  // 0x4B Keypad 4
        {'5', 0xCC},  // 0x4C Keypad 5
        {0x7D, 0xCD},  // 0x4D Keypad 6
        {'+', 0xCE},  // 0x4E Keypad +
        {'1', 0xCF},  // 0x4F Keypad 1
        {0x7A, 0xD0},  // 0x50 Keypad 2
        {'3', 0xD1},  // 0x51 Keypad 3
        {'0', 0xD2},  // 0x52 Keypad 0
        {'.', 0xD3},  // 0x53 Keypad .
        // 0xE0 extended key prefix and more codes can be added here
};

#endif
