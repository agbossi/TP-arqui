#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

void zeroDivision();
void invalidOperationCode();
void printRegister(uint64_t value, uint64_t num);
void printStackFrame(uint64_t rsp);
void loadExceptions();
void exceptionDispathcer(int exception, uint64_t rsp);


#endif
