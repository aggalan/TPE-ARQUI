#include <lib.h>
#include <naiveConsole.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <keyboardBuffer.h>
#include "registers.h"
#include "interrupts.h"


void keyboard_handler(){

	char key = get_key();

    if (key == 0) {
        return;
    }
    // if(key == 0x39){
    //    buffer_append(key);
    //    return;
    // }
    
    if(ScanCodes[key] == ';'){
        saveRegState();
        register_snapshot_taken = 1;
        return;
    }
    buffer_append(key);

    
    


    // if (key >= 0 && key < 256 && ScanCodes[key] != 0) {
    //     buffer_append(ScanCodes[key]);
    //     if(ScanCodes[key] == '\b'){
    //         buffer_backspace();
    //     }
    //     if (ScanCodes[key] == '\n') {
    //         buffer_clear(2);
    //     }
    //     if(ScanCodes[key] == '\t'){
    //         tab();
    //     }

    //     return;
    // }

    
}
