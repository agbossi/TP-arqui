#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H
#include <stdint.h>

void loadVideoDriver();
void setTerminal(int t);
void getResolution(int * x, int * y);
void scrollUp();
void eraseCharacter();
void newLine();
void printChar(char c);
void moveCursorLeft();
void moveCursorRight();
void putCharAt(char c, int index);
void blink();
void putPixelAt(int colour, int x, int y);
void printDec(uint64_t value);
void printHex(uint64_t value);
void printBin(uint64_t value);
void printBase(uint64_t value, uint32_t base);
void printString(const char * string);
void clearScreen();
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);


#endif
