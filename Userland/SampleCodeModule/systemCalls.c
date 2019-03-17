#include "systemCalls.h"
#include <interrupt.h>
#include "stdio.h"

void write(char *buffer, unsigned int size)
{
	int80h(1, (unsigned long) buffer, (unsigned long)size,0,0,0);
}
void read(char *buffer, unsigned int size)
{
	int80h(2, (unsigned long) buffer, (unsigned long)size,0,0,0);
}
void setTerminal(unsigned long size)
{
	int80h(3,size,0,0,0,0);
}
void time(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9)
{
	int80h(4,rsi,rdx,rcx,r8,r9);
}
void printGraphic(int color,int x,int y)
{
	int80h(5, (unsigned long) color, (unsigned long)x,(unsigned long)y,0,0);
}
void getResolution(int *height,int * width)
{
	int80h(6, (unsigned long) height, (unsigned long)width,0,0,0);
}
void backspace()
{
	int80h(7,0,0,0,0,0);
}
void newline()
{
	int80h(8,0,0,0,0,0);
}
void clearScreen()
{
	int80h(0,0,0,0,0,0);
}
