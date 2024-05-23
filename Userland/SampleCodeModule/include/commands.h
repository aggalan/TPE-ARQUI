#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define COMMANDS_SIZE 10

void seek_command(char * buff);
void call_command(int i, char * command);
void help();
void time();
void div0();
void invalidOp();

enum Commands {
    HELP,
    TIME,
    REGSTATE,
    DIVZERO,
    INVALIDOP,
    ELIMINATOR,
    INCFONT,
    DECFONT,
    FONTSIZE,
    CLEAR

};



#endif