#include <lib.h>
#include <naiveConsole.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <keyboardBuffer.h>
#include "registers.h"
#include "interrupts.h"



void keyboard_handler(){

	uint16_t key = get_key();

    if (key == 0) {
        return;
    }

    if (get_shift_val() == 0 && key == 0x2A) {
        set_shift(1);
        return;
    } else if (get_shift_val() == 1 && key == 0xAA) {
        set_shift(0);
        return;
    }

    if (get_shift_val() == 0 && key == 0x36) {
        set_shift(2);
        return;
    } else if (get_shift_val() == 2 && key == 0xB6) {
        set_shift(0);
        return;
    }

//    if (key == 0x3A && get_shift_val() != 0) {
//        set_shift(0);
//        return;
//    } else if (key == 0x3A && get_shift_val() == 0) {
//        set_shift(1);
//        return;
//    }





    if(ScanCodes[key].make == ';'){
        saveRegState();
        register_snapshot_taken = 1;
        return;
    }
    
     buffer_append(key);


}
