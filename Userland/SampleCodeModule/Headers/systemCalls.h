#ifndef SYSTEM_CALLS_H_
#define SYSTEM_CALLS_H_

void int80h(unsigned long rdi, unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);
void write(char *buffer, unsigned int size);
void read(char *buffer, unsigned int size);
void setTerminal(unsigned long size);
void time(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);
void printGraphic(int color, int x, int y);
void getResolution(int *height,int * width);
void backspace();
void newline();
void clearScreen();

#endif
