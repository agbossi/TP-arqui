#include "exceptions.h"

#pragma pack(push)
#pragma pack (1)
//https://os.phil-opp.com/better-exception-messages/
typedef struct {
  uint64_t ip; //instruction pointer
  uint64_t cs; //code segment
  uint64_t flags; 
  uint64_t sp; //stack pointer
  uint64_t ss; //stack segment
} exceptionStackFrame;

#pragma pack(pop)

typedef void (* exception)(uint64_t rsp);

static exception exceptions[32]; //las primeras 32 de la tabla son excepciones

void exceptionDispatcher(int exception, uint64_t rsp) 
{
	if (exception == 0 || exception == 6)
	{
		exceptions[exceptionID](rsp);
		printStackStatus(rsp);
	}
}

void printRegister(uint64_t value, uint64_t num) 
{
	printString(": 0x");
	printHex(value);
	printString("  ");
	if(num % 4 == 0)
		printChar('\n');
}

void printStackStatus(uint64_t rsp) 
{
	exceptionStackFrame * exceptionInfo = (uint64_t*) rsp;

	printString("Instruction pointer: ");
	printHex(exceptionInfo->ip);
	printChar('\n');

	printString("Code segment: ");
	printHex(exceptionInfo->cs);
	printChar('\n');

	printString("CPU flags: ");
	printHex(exceptionInfo->flags);
	printChar('\n');

	printString("Stack pointer: ");
	printHex(exceptionInfo->sp);
	printChar('\n');

	printString("Stack segment: ");
	printHex(exceptionInfo->ss);
	printChar('\n');

	printString("Registers: \n");
}

void loadExceptions()
{
	exceptions[0] = zeroDivision;
	exceptions[4] = overflow;
	exceptions[6] = invalidOperationCode;
}

static void zeroDivision(uint64_t rsp)
{
	printString("Zero division: \n");
}

static void invalidOperationCode(uint64_t rsp)
{
	printString("Invalid opcode exception: \n");
}
