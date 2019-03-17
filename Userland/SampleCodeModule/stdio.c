#include "systemCalls.h"
#include "stdlib.h"
#include <stdarg.h>
#include "stdio.h"

char buffer[25*80];

void putchar(char letter)
{
	write(&letter, 1);
}

char getchar()
{
	char letter;
	do{
	read(&letter, 1);
	}while(letter == -1);
	return letter;
}

int printf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	//char * fmt = format;
	char buffer[12];
	char * str;
	int length, number_to_print;
	while(*(format) != 0){
		if(*(format) == '%'){
			switch(*(format + 1)){
				case 'd':
					number_to_print = (int) va_arg(args, int);
					length = itoa(number_to_print, buffer, 10);
					write(buffer, length);
					format++;
					break;
				case 'c':
					putchar((char) va_arg(args, int));
					format++;
					break;
				case 's':
					str = (char*) va_arg(args, char*);
					write(str, strlen(str));
					format++;
					break;
				case 'x':
					number_to_print = (int) va_arg(args, int);
					length = itoa(number_to_print, buffer, 16);
					format++;
					break;
			}
		}else{
			putchar(*(format));
		}
		format++;
	}
	return 0;
}

void printTime()
{
	int seconds;
	int minutes;
	int hours;
	int month;
	int year = 0;
	time(&seconds, &minutes, &hours, &month, &year);
	if(hours == 0)
	{
		printf("%d : %d : %d", 9, minutes, seconds);
		return;
	}else if(hours == 1){
		printf("%d : %d : %d", 10, minutes, seconds);
		return;
	}else if(hours == 2){
		printf("%d : %d : %d", 11, minutes, seconds);
		return;
	}else{
		printf("%d : %d : %d", hours - 3 , minutes, seconds);
		return;
	}
}

int scanf(const char* format, ...){
	va_list args;
	va_start(args, format);
	char c;
	int * p;
	char * pc;
	int aux = 0, num = 0, len = 0,i = 1, negative = 0;
	readline(buffer);
	c = buffer[0];
	while(c != '\n')
	{
		if(*format == '%')
		{
			switch(*(format + 1))
			{
				case 'd':
					if((c >= '0' && c <= '9') || c == '-'){
						p = (int*) va_arg(args, int*);
						if(c == '-')
							negative = 1;
						do{
							aux = c - '0';
							num = (num*10) + aux;
							*p = num;
							c = buffer[i];
							i++;
						}while(c >= '0' && c <= '9');

						if(negative == 1)
							*p *= -1;
						format +=2;
						len++;
					}else{
						return len;
					}
					break;

				case 'c':
					if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						pc = (char*) va_arg(args, char*);
						*pc = c;
						c = buffer[i];
						i++;
						format += 2;
						len++;
					}else{
						return len;
					}
					break;

				case 's':
					if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
					{
						pc = (char*) va_arg(args, char*);
						do {
							*(pc + aux) = c;
							aux++;
							c = buffer[i];
							i++;
						}while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
						aux = 0;
						format += 2;
						len++;
					}else{
						return len;
					}
					break;
				}
		}else if(c == *format){
			c = buffer[i];
			i++;
			format++;
		}else{
			return len;

		}
	}
	return len;
}

void readline(char* buff)
{
	int j;
	for(j=0; (buff[j-1] != '\n') ; j++)
	{
		do{
		buff[j] = getchar();
		printf("%c", buff[j]);
		if(buffer[j] == '\b')
		{
			buff[j] = 0;
			buff[j-1] = 0;
			j -= 2;
		}
		}while(buff[j] == -1);
	}
}
