#include <time.h>
#include <stdint.h>
#include <naiveConsole.h>
#include "syscall.h"
#include "videoDriver.h"
#include "registers.h"
#include "interrupts.h"
#include "soundDriver.h"


static void int_20();
static void int_21();
static uint64_t int_80(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10);
typedef void (*InterruptHandler)(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10);

void irqDispatcher(uint64_t irq, uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10) {
	InterruptHandler interruptions[256] = {0};
	interruptions[0] = &int_20;
	interruptions[1] = &int_21;
	interruptions[96] = (InterruptHandler)int_80;

	if(irq >= 0 && irq < 256 && interruptions[irq] != 0 ){
		InterruptHandler handler = interruptions[irq];
		handler(rax, rdi, rsi, rdx, r10);
	}
}

void int_20() {
	timer_handler();
    if (ticks_elapsed() % 21 <= 10) {
        cursorOn();
    } else {
        cursorOff();
    }

}
void int_21(){
	keyboard_handler();
}

uint64_t int_80(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10){
	switch(rax){
		case 1: 
				sys_write((char *)rdi, rsi, rdx);
				break;
		case 2:
				sys_read((char *)rdi, rsi, rdx);
				break;
		case 3: 
				TimeClock((char *)rdi); //chequear
				break;
		case 4:
				printRegistersASM(); 
				break;
		case 5: 
				size_up();
				break;
		case 6: 
				size_down();
				break;
		case 7: 
				clear();
				break;
		case 8:
				fontSize();
				break;
		case 9:
				beep(rdi, rsi);
				break;
	}
}
