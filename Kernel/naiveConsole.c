#include <naiveConsole.h>
#define defaultColor 0x0F
#define defaultBack 0x00

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void ncPrint(const char * string)
{
	for (int i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintColor(const char * string, char color, char back){
	
	for (int i = 0; string[i] != 0; i++)
		ncPrintCharColor(string[i], color, back);
}

void ncPrintCharColor(char character, char color, char back){
	*currentVideo = character;
	char font = color | back;
	currentVideo++;
	*currentVideo = font;
	currentVideo++;
}

void ncPrintChar(char character)
{
	ncPrintCharColor(character, defaultColor, defaultBack);
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;

}
void ncBackspace(){
	if(currentVideo >= 0xB8002){
		currentVideo -= 2;
		*currentVideo = ' ';
	}
}


uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
void convertToGMTMinus3(int *hours, int *days, int *month, int *year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int monthDays = daysInMonth[(*month - 1) % 12];
    
    if (*year % 4 == 0 && (*year % 100 != 0 || *year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    *hours -= 3;
    if (*hours < 0) {
        *hours += 24;
        *days -= 1;
        if (*days < 1) {
            *month -= 1;
            monthDays = daysInMonth[(*month - 1) % 12];
            if (*month < 1) {
                *month = 12;
                *year -= 1;
            }
            *days = monthDays;
        }
    }
}

int get_hours();
int get_minutes();
int get_seconds();
int get_wday();
int get_mday();
int get_month();
int get_year();

char * TimeClock(char * buffer) {
    char * days[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
    int hours = get_hours();
    int minutes = get_minutes();
    int seconds = get_seconds();
    int weekday = get_wday();
    int monthDay = get_mday();
    int month = get_month();
    int year = get_year();
    
    int originalDay = monthDay;
    
    convertToGMTMinus3(&hours, &monthDay, &month, &year);

    if (monthDay != originalDay) {
        weekday -= 1;
        if (weekday < 1)
            weekday = 7; 
    }
    
    int digits = uintToBase(hours, buffer, 10);
    buffer[digits++] = ':';
    digits += uintToBase(minutes, buffer + digits, 10);
    buffer[digits++] = ':';
    digits += uintToBase(seconds, buffer + digits, 10);
    buffer[digits++] = ' ';
    for (int i = 0; i < 3; i++)
        buffer[digits++] = days[weekday - 1][i];
    buffer[digits++] = ' ';
    digits += uintToBase(monthDay, buffer + digits, 10);
    buffer[digits++] = '/';
    digits += uintToBase(month, buffer + digits, 10);
    buffer[digits++] = '/';
    digits += uintToBase(year, buffer + digits, 10);
    buffer[digits++] = ' ';
    buffer[digits] = 0;
    return buffer;
}

