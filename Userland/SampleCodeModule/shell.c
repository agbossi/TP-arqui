
#include "systemCalls.h"
#include "stdlib.h"
#include "stdio.h"
#include "interrupt.h"

void invalidOperationCode();

int time_colour = 0;

int width = 1;
int height = 1;

void setVideo(){
  getResolution(&height,&width);
}

void newLine() {
    printf("\nUser$ >");
}

void printHelpMenu() {
    printf("==========================================================\n");
    printf("|| dixit - REPEAT WHAT YOU JUST SAID                    ||\n"); //lo agregue porque era facil de hacer y me parecia piola para sumar puntitos jajaja
    printf("|| time - CHECK CURRENT TIME IN ARGENTINA               ||\n");
    printf("|| cls - CLEAR ALL CONTENT FROM THE SCREEN              ||\n");
    printf("|| zero - PERFORM A DIVISION BY ZERO AND RETRIEVE DATA  ||\n");
    printf("|| ioc - PERFORM AN INVALID OPERATION AND RETRIEVE DATA ||\n");
    printf("|| help - DISPLAY AVAILABLE COMMANDS                    ||\n");
    printf("|| exit - EXIT THE TERMINAL                             ||\n");
    printf("==========================================================\n");
    newLine();
}

int analyzeEntry(char* input) {    
    if(strncmp(input, "dixit ", 5) == 0) {
    char* phrase = &(input[6]);
      printf("%s\n", phrase);
      printf("%s", "User$ >");
      return 0;
    }else if(strcmp(input, "time") == 0) {
      printTime();
      newLine();
      return 0;
    }else if(strcmp(input, "cls") == 0) {
      clearScreen();
      newLine();
      return 0;
    }else if(strcmp(input, "help") == 0) {
     printHelpMenu();
     return 0;
    }else if(strcmp(input, "exit") == 0) {
     return 1;
    }else if(strcmp(input, "zero") == 0) {
      printf("%d\n",4/0);
    }else if(strcmp(input, "ioc") == 0) {
      invalidOperationCode();
    }else{
      printf("Wrong command\n");
      printf("User$ >");
    }
    return -1;
}


void shell(){
  char buffer[25*80];
  int i = 0, flag = 1;
  char c;
  char * user = "User$ >"; //punto de partida de la terminal
  setTerminal(strlen(user));
  if (flag)
  { //MENSAJE DE BIENVENIDA
    printf("\n");
    printf("Hello, welcome to the new Operating System\n");
    printf("Type 'help' for the list of commands\n");
    printf("User$ >");
    flag = 0;
  }else{
    newLine();
  }
  while(1) { //LOOP DE LECTURA DE ENTRADA
   if ((c = getchar()) != -1) {
     if(c == '\b') 
     { //borrado de caracter
       if(i != 0) 
       { //chequeo que no sea el primero asi no pisa User$ > 
         i--;
         buffer[i] = 0; 
         putchar(c);
         backspace();
       }
      } else {
        if(c == '\n') 
        {//enter 
         putchar(c);
         buffer[i] = 0;
         if(analyzeEntry(buffer) == 1) //entrada de datos valida
           return;
         i = 0; //reseteo porque termino la lectura de linea de comando
         buffer[i] = 0;
        }else{
         buffer[i] = c;
         i++;
         buffer[i] = 0;           
         putchar(c);
       }
     }
   }
  }
}
