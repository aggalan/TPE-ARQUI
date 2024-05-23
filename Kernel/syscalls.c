#include <naiveConsole.h>
#include <syscall.h>
#include <keyboardBuffer.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <interrupts.h>


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
        // int pos = get_pos();
        for (i = 0; i < len;) {
            _hlt();
            aux = getBuffAtCurrent();
            if (aux > 0 && aux <= 255) {
                if (aux == 0x39) {
                    c[i++] = ' ';
                } else {
                    c[i++] = ScanCodes[(int) aux];
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

