#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <syscalls.h>
#include <videoDriver.h>
#include <font.h>
#include "idtLoader.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * retUserLand(){
	return sampleCodeModuleAddress;
}

void * initializeKernelBinary()
{
	char buffer[10];
	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{
	load_idt();
//    int x = 1024/2;
//    int y = 762/2;
//    for (int i =0; i < NOSOTROS_HEIGHT * NOSOTROS_WIDTH;i++) {
//        putPixel(NOSOTROS[i], x++, y);
//        if (x == NOSOTROS_WIDTH + 1024/2) {
//            x = 1024/2;
//            y++;
//        }
//    }
//	char buffer[64]={0};
//	ncPrint(TimeClock(buffer));
//	ncPrintColor("Arquitectura de computadoras", 0xF0, 0x0A);
//	ncNewline();
//	while(1){
//		keyboard_handler();
//	}
//	ncPrint("[Kernel Main]");
//	ncNewline();
//	ncPrint("  Sample code module at 0x");
//	ncPrintHex((uint64_t)sampleCodeModuleAddress);
//	ncNewline();
//	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	while(1);
//	ncNewline();
//	ncNewline();

//	ncPrint("  Sample data module at 0x");
//	ncPrintHex((uint64_t)sampleDataModuleAddress);
//	ncNewline();
//	ncPrint("  Sample data module contents: ");
//	ncPrint((char*)sampleDataModuleAddress);
//	ncNewline();

//	ncPrint("[Finished]");
	return 0;
}
