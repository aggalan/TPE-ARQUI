#include <shell.h>
#include <userSyscalls.h>
#include <commands.h>
#include <buffer.h>
#include "colors.h"
#include "utils.h"


static char buff[BUFFERLIMIT] = {0};
static char prev_commands[10][BUFFERLIMIT] = {{0}};
static int prev_num = 0;
static int count_num = 0;

void welcome_message(){
    //call_paint_screen(BLACK);
    char welcome_message[] = "Welcome to NegrOS.\nInput a command: \n(Enter HELP to see full list of commands)\n";
    for(int i = 0; welcome_message[i] != 0; i++){
        putCh(welcome_message[i]);
    }

}

void line_start(){
    putCh('$');
    clearBuff(buff);
}


void bufferize(){
    
    int i = 0;
    int end_buff = 0;
    int flag = 0;
    int timer = 0;
    int max_pos = 0;
//    call_cursor_on();
    while (i < BUFFERLIMIT){
        char c = getCh();
        end_buff = (i == BUFFERLIMIT-1);
        if(c == '\b'){
            if(i > 0){
                if (buff[--i] == '\t') {
                    putCh('\b');
                }
//                putCh('\n');
//                print(buff);

                int j = i;
                while (buff[j] != 0) {
                    buff[j] = buff[j+1];
                    j++;
                }
//                buff[i] == 0;
//                print(buff);

                max_pos--;
            }
            else flag = 1;
        }
        else if(c == '\n'){
            max_pos = 0;
            putCh(c);
            if( i == 0 && buff[i] == 0){
               clearBuff(buff);
                return;
            }

//            for (int p = 0; buff[p] != 0; p++) {
//                prev_commands[count_num][p] = buff[p];
//            }
//            count_num++;

//            buff[i] = 0;
            read_command(buff);
            return;
        } else if (c == 0x7C){
            if (i > 0) {
                i--;
            } else {
                flag = 1;
            }
        }
        else if(c == 0x7D) {
//            putCh(max_pos + '0');
            if (i < BUFFERLIMIT && i < max_pos) {
                i++;
            } else {
                flag = 1;
            }
        }
//        else if (c == 0x7B) {
//            if (prev_num < count_num) {
//                clearBuff(buff);
//                i = 0;
//                while(prev_commands[prev_num][i] != 0) {
//                    buff[i] = prev_commands[prev_num][i];
//                    putCh(buff[i]);
//                    i++;
//                }
//                prev_num++;
//            }
//            flag = 1;
//        }
        else{
            if(!end_buff && c != 0 && max_pos < BUFFERLIMIT-1) {
                max_pos++;
                int z = BUFFERLIMIT-1;
                while(z != i) {
                    buff[z] = buff[z-1];
                    z--;
                }

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
    call_clear();
    welcome_message();
    while(1){
        line_start();
        bufferize();
    }
    return 0;
}