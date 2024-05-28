#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H


 
// static char ScanCodes[256] = {
//    0,   // 0x00 - Null
//    0,   // 0x01 - Escape
//    '1', // 0x02 - '1'
//    '2', // 0x03 - '2'
//    '3', // 0x04 - '3'
//    '4', // 0x05 - '4'
//    '5', // 0x06 - '5'
//    '6', // 0x07 - '6'
//    '7', // 0x08 - '7'
//    '8', // 0x09 - '8'
//    '9', // 0x0A - '9'
//    '0', // 0x0B - '0'
//    '-', // 0x0C - '-'
//    '=', // 0x0D - '='
//    '\b', // 0x0E - Backspace
//    '\t', // 0x0F - Tab
//    'Q', // 0x10 - 'Q'
//    'W', // 0x11 - 'W'
//    'E', // 0x12 - 'E'
//    'R', // 0x13 - 'R'
//    'T', // 0x14 - 'T'
//    'Y', // 0x15 - 'Y'
//    'U', // 0x16 - 'U'
//    'I', // 0x17 - 'I'
//    'O', // 0x18 - 'O'
//    'P', // 0x19 - 'P'
//    '[', // 0x1A - '['
//    ']', // 0x1B - ']'
//    '\n', // 0x1C - Enter
//    0,   // 0x1D - Control (Left Ctrl)
//    'A', // 0x1E - 'A'
//    'S', // 0x1F - 'S'
//    'D', // 0x20 - 'D'
//    'F', // 0x21 - 'F'
//    'G', // 0x22 - 'G'
//    'H', // 0x23 - 'H'
//    'J', // 0x24 - 'J'
//    'K', // 0x25 - 'K'
//    'L', // 0x26 - 'L'
//    ';', // 0x27 - ';'
//    '\'', // 0x28 - '''
//    '`', // 0x29 - '`'
//    0,   // 0x2A - Shift (Left Shift)
//    '\\', // 0x2B - '\'
//    'Z', // 0x2C - 'Z'
//    'X', // 0x2D - 'X'
//    'C', // 0x2E - 'C'
//    'V', // 0x2F - 'V'
//    'B', // 0x30 - 'B'
//    'N', // 0x31 - 'N'
//    'M', // 0x32 - 'M'
//    0,   // 0x33 - ',' (comma)
//    0,   // 0x34 - '.' (period)
//    0,   // 0x35 - '/' (forward slash)
//    0,   // 0x36 - Shift (Right Shift)
//    0,   // 0x37 - (Print Screen)
//    0,   // 0x38 - Alt (Left Alt)
//    ' ', // 0x39 - Space
//    0,   // 0x3A - Caps Lock
//    0,   // 0x3B - (F1)
//    0,   // 0x3C - (F2)
//    0,   // 0x3D - (F3)
//    0,   // 0x3E - (F4)
//    0,   // 0x3F - (F5)
//    0,   // 0x40 - (F6)
//    0,   // 0x41 - (F7)
//    0,   // 0x42 - (F8)
//    0,   // 0x43 - (F9)
//    0,   // 0x44 - (F10)
//    0,   // 0x45 - Num Lock
//    0,   // 0x46 - Scroll Lock
//    0, // 0x47 - Numpad 7
//    0, // 0x48 - Numpad 8
//    0, // 0x49 - Numpad 9
//    0, // 0x4A - Numpad '-'
//    0x7C, // 0x4B - Numpad 4
//    0, // 0x4C - Numpad 5
//    0x7D, // 0x4D - Numpad 6
//    0, // 0x4E - Numpad '+'
//    0, // 0x4F - Numpad 1
//    0, // 0x50 - Numpad 2
//    0, // 0x51 - Numpad 3
//    0, // 0x52 - Numpad 0
//    0, // 0x53 - Numpad '.'
//    0,   // 0x54 - (Unused)
//    0,   // 0x55 - (Unused)
//    0,   // 0x56 - (Unused)
//    0,   // 0x57 - (F11)
//    0,   // 0x58 - (F12)
//    0,   // 0x59 - (Unused)
//    0,   // 0x5A - (Unused)
//    0,   // 0x5B - (Unused)
//    0,   // 0x5C - (Unused)
//    0,   // 0x5D - (Unused)
//    0,   // 0x5E - (Unused)
//    0,   // 0x5F - (Unused)
//    0,   // 0x60 - (Unused)
//    0,   // 0x61 - (Unused)
//    0,   // 0x62 - (Unused)
//    0,   // 0x63 - (Unused)
//    0,   // 0x64 - (Unused)
//    0,   // 0x65 - (Unused)
//    0,   // 0x66 - (Unused)
//    0,   // 0x67 - (Unused)
//    0,   // 0x68 - (Unused)
//    0,   // 0x69 - (Unused)
//    0,   // 0x6A - (Unused)
//    0,   // 0x6B - (Unused)
//    0,   // 0x6C - (Unused)
//    0,   // 0x6D - (Unused)
//    0,   // 0x6E - (Unused)
//    0,   // 0x6F - (Unused)
//    0,   // 0x70 - (Unused)
//    0,   // 0x71 - (Unused)
//    0,   // 0x72 - (Unused)
//    0,   // 0x73 - (Unused)
//    0,   // 0x74 - (Unused)
//    0,   // 0x75 - (Unused)
//    0,   // 0x76 - (Unused)
//    0,   // 0x77 - (Unused)
//    0,   // 0x78 - (Unused)
//    0,   // 0x79 - (Unused)
//    0,   // 0x7A - (Unused)
//    0,   // 0x7B - (Unused)
//    0,   // 0x7C - (Unused)
//    0,   // 0x7D - (Unused)
//    0,   // 0x7E - (Unused)
//    0    // 0x7F - (Unused)
//};


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
        {'8', 0xC8},  // 0x48 Keypad 8
        {'9', 0xC9},  // 0x49 Keypad 9
        {'-', 0xCA},  // 0x4A Keypad -
        {0x7C, 0xCB},  // 0x4B Keypad 4
        {'5', 0xCC},  // 0x4C Keypad 5
        {0x7D, 0xCD},  // 0x4D Keypad 6
        {'+', 0xCE},  // 0x4E Keypad +
        {'1', 0xCF},  // 0x4F Keypad 1
        {'2', 0xD0},  // 0x50 Keypad 2
        {'3', 0xD1},  // 0x51 Keypad 3
        {'0', 0xD2},  // 0x52 Keypad 0
        {'.', 0xD3},  // 0x53 Keypad .
        // 0xE0 extended key prefix and more codes can be added here
};


void keyboard_handler();
extern int get_key();

#endif
