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

    if (key == 0x2A) {
        shift_active();
        return;
    } else if (key == 0xAA) {
        shift_dropped();
        return;
    }

    if(ScanCodes[key].make == ';'){
        saveRegState();
        register_snapshot_taken = 1;
        return;
    }
    
     buffer_append(key);


}
