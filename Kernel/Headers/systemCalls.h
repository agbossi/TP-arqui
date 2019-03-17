#ifndef SYSTEM_CALLS_H_
#define SYSTEM_CALLS_H_

void loadSystemCalls();
void systemHandler(int num,char*buffer,int size);
void systemTime(unsigned long sec, unsigned long min, unsigned long hour, unsigned long month, unsigned long year);
void systemClear(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemWrite(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemTerminal(unsigned long size, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemRead(unsigned long buffer, unsigned long size, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemGraphic(unsigned long color, unsigned long x, unsigned long y, unsigned long r8, unsigned long r9);
void systemResolution(unsigned long height, unsigned long width, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemEraseCharacter(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);
void systemNewLine(unsigned long rsi, unsigned long rdx, unsigned long rcx, unsigned long r8, unsigned long r9);

#endif