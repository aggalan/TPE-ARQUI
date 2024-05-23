#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include "registers.h"
#include <stdint.h>

void exceptionDispatcher(int exception, registerStruct * registers);
void zero_division();
void invalid_op();

#endif