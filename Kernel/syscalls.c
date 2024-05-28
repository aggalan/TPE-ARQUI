#include <naiveConsole.h>
#include <syscall.h>
#include <keyboardBuffer.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <interrupts.h>

static int shift = 0;

void shift_active() {
    shift = 1;
}

void shift_dropped() {
    shift = 0;
}

void sys_write(const char * buff, int len, int fd){

    if(fd == 1){
        drawWordLen(buff, len);
        
    } else if(fd == 2){
        drawWordColorLen(buff, WHITE, RED, len);
    }else
    invalidFD();

}

void sys_read(char * c, int len, int fd){

    int i;

    if (fd == 0) {
        char aux = 0;
        for (i = 0; i < len;) {
            _hlt();
            aux = getBuffAtCurrent();
            if (aux > 0 && aux <= 255) {


                if (shift == 1 && ScanCodes[(int)aux].make >= 'a' && ScanCodes[(int)aux].make <= 'z') {
                    c[i++] = ScanCodes[(int)aux].make - 32;
                } else {
                    c[i++] = ScanCodes[(int)aux].make;
                }


                consume();
            }

        }
        return;
    }
    else{
        invalidFD();
    }
}

