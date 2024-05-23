#include <shell.h>
#include <userSyscalls.h>
#include <commands.h>
#include <buffer.h>
#include "colors.h"
#include "utils.h"


static char buff[BUFFERLIMIT] = {0};

void welcome_message(){
    //call_paint_screen(BLACK);
    char welcome_message[] = "Wellcome to The Shell.\nInput a command: \n(Enter HELP to see full list of commands)\n";
    for(int i = 0; welcome_message[i] != 0; i++){
        putCh(welcome_message[i]);
    }

}

void line_start(){
    putCh('$');
    clearBuff(buff);
}

// lee caracteres y los almacena en el buffer hasta que:
// El buff se llene, se encuentre un backspace o un enter

void bufferize(){
    int i = 0;
    int end_buff = 0;
    int flag = 0;
    while (i < BUFFERLIMIT){
        char c = getCh();
        end_buff = (i == BUFFERLIMIT-1);
        if(c == '\b'){
            if(i > 0){
                buff[i--] = 0;
            }
            else flag = 1;
        }
        else if(c == '\n'){
            putCh(c);
            if( i == 0){
               clearBuff(buff);
                return;
            }
            buff[i] = 0;
            read_command(buff);
            return;
        } else{
            if(!end_buff && c != 0) {
                buff[i++] = c;
            }else {
                flag = 1;
            }
        }
        if(!flag && c != 0) {
            putCh(c);
        }

        flag = 0;
    }

    return;


}

void read_command(char * buff){
    seek_command(buff);
    clearBuff(buff);

}


int shell_start(){
    welcome_message();
    while(1){
        line_start();
        bufferize();
    }
    return 0;
}