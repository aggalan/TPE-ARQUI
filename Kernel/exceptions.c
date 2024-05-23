#include "exceptions.h" //armar
#include "registers.h"
#include "syscall.h"
#include "videoDriver.h"
#define ZERO_EXCEPTION_ID 0
 



void exceptionDispatcher(int exception, registerStruct * registers) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else {
		invalid_op();
	}
	printRegisters(registers);
	drawWordColor("Press a key to continue",WHITE, RED);
	char c;
	sys_read(&c, 1, 0);
    buffer_clear();
}

 void zero_division() {
	register_snapshot_taken = 1;
	drawWordColor("ERROR: CANNOT DIVIDE BY ZERO", WHITE, RED);
	newline();
}

 void invalid_op(){
	register_snapshot_taken = 1;
	drawWordColor("ERROR: INVALID OPCODE", WHITE, RED);
	newline();
}

