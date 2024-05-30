#ifndef _SHELL_H_
#define _SHELL_H_

#define COMMAND_SIZE 10
#include "utils.h"

void welcome_message();
void line_start();
void bufferize();
void read_command(char * buff);
int shell_start();

#endif