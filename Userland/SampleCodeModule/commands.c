//agregar includes
//definir el commands size en el .h
#include "commands.h"
#include "syscall.h"
#include "utils.h"
#include "invalidOp.h"

static char commands[COMMANDS_SIZE][14] = {"HELP", "TIME", "REGSTATE", "DIVZERO", "INVALIDOP", "ELIMINATOR", "INCFONT", "DECFONT","FONT", "CLEAR" };

void seek_command(char * buff){
    for(int i = 0; i < COMMANDS_SIZE; i++){
        if(strcmpspace(commands[i], buff) == 0){
            call_command(i, buff);
            return;
        } 
    }
    call_command(-1, buff); 
}

void call_command(int i, char * command){
    switch(i){
        case HELP:;
            help();
            return;
        case TIME:;
            time();
            return;
        case REGSTATE:;
            call_reg_state();
            return; 
        case DIVZERO:;
            div0();
            return;
        case INVALIDOP:;
            invalidOpASM();
            return;
        case ELIMINATOR:;
            //eliminator(); //falta hacer jueguito
            return;
        case INCFONT:;
            call_size_up();
            return;
        case DECFONT:;
            call_size_down();
            return;
        case FONT:;
            call_font();
            return;
        case CLEAR:;
            call_clear(); 
            return;
        default:;
            call_sys_write("ERROR - Command not found",30,2);
            putCh('\n');
            return;
    }
}

void help(){
    call_sys_write("Available commands:\n", 20, 1);
    for(int i = 0; i < COMMANDS_SIZE; i++){
        call_sys_write(commands[i], 12, 1); //esto deberia ser un printf no un call sys write creo, porque cada uno se caga
        call_sys_write("\n", 1, 1);
    }
}

void time(){
    char clock[50];
    call_time_clock(clock); 
    char c;
    for(int i = 0; (c = clock[i]) != 0; i++){
        putCh(c);
    }
    putCh('\n');
}


void div0(){
    int a = 0;
    int b = 2;
    a = b/a;
}

void invalidOp(){
    invalidOpASM();
}
