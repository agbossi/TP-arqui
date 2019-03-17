#include "include/keyboardDriver.h"
#include "include/videoDriver.h"
#include "kernel.h"

extern int getSeconds();
extern int getMinutes();
extern int getHours();
extern int getMonth();
extern int getYear();


typedef void (*syscall)(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

static syscall systemCallArray[9];

void loadSystemCalls()
{
	systemCallArray[0]= &systemclear;
	systemCallArray[1]= &systemwrite;
	systemCallArray[2]= &systemread;
	systemCallArray[3]= &systemsetTerminal;
	systemCallArray[4]= &systemtime;
	systemCallArray[5]= &systemgraphic;
	systemCallArray[6]= &systemresolution;
	systemCallArray[7]= &systembackspace;
	systemCallArray[8]= &systemnewline;
}

void systemHandler(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	if (rdi >= 0 && rdi <= 6)
		systemCallArray[rdi](rsi,rdx,rcx,r8,r9);
	return;
}

void systemTime(unsigned long sec, unsigned long min, unsigned long hour, unsigned long month, unsigned long year)
{
	int * segundos=(int *) sec;
	int * minutos=(int *) min;
	int * horas=(int *) hour;
	int * meses=(int *) month;
	int * anos=(int *) year;
	(*segundos) = getSeconds();
	(*minutos) = getMinutes();
	(*horas) = getHours();
}

void systemClear(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	clearScreen();
}

void systemWrite(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	char * c = (char*) buffer;
	for (int i = 0; i < size; i++)
	{
		printChar(c[i]);
	}
}

void systemTerminal(unsigned long size, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	setTerminal((int)size);
}

void systemRead(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	char * buff= (char*) buffer;
	for (int i = 0 ; i < size ; i++)
	{
		*(buff + i) = getBuffer();
	}
}

void systemGraphic(unsigned long color, unsigned long x, unsigned long y, unsigned long r8, unsigned long r9)
{
	putPixelAt((int) color, (int) x, (int) y);
}

void systemResolution(unsigned long height, unsigned long width, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	getResolution((int *) height, (int *) width);
}

void systemEraseCharacter(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	eraseCharacter();
}

void systemNewLine(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	newLine();
}
