#include <keyboardDriver.h>
#include <videoDriver.h>

#define BUFFER_SIZE 2000
#define LEFT 129
#define RIGHT 130
#define CAPS 131
#define SHIFT 132

unsigned char characters[128] = { 0,  27, '1', '2', '3', '4', '5', '6', '7', '8','9', '0', '-', '=', '\b',
                                '\t',	'q', 'w', 'e', 'r','t', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
                                  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0, '\\',
                                 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,'*', 0, ' ', 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0,	0, 0,	0, '-', LEFT,	0, RIGHT,	'+',
                                  0, 0, 0, 0,	0, 0, 0, 0, 0, 0,	0};

static char buffer[BUFFER_SIZE];
static int index = 0;
static int buffer_index = 0;
static uint8_t caps = 0;
static uint8_t shift = 0;

void keyboardHandler()
{
    unsigned char keycode;
    keycode = getKeyPressed();
    
    if (keycode & 0x80)
    {
		  if(keycode == 0x2A || keycode == 0XAA|| keycode == 0x36 || keycode == 0xB6) //direcciones de la tecla SHIFT
      {
    		shift = !shift;
			return;
		  }
    } else {
    	char key = characters[keycode]; //direccion de LEFT ARROW
    	if (keycode == 0x4B)
    	{
    		cursorLeft();
    		return;
    	}
    	if (keycode == 0x4D) //direccion de RIGHT ARROW
    	{
    		cursorRight();
    		return;
    	}
      if(keycode == 0x2A || keycode == 0XAA|| keycode == 0x36 || keycode == 0xB6)
        {
        	shift = !shift;
			return;
		}
		else if(keycode == 0x3A)
		  { //direcicon de CAPS
	      caps = !caps;
	      return;
		  }
		  if (shift || caps)
		  {
       		if (key == '0')
       		{
	        	buffer[buffer_index] = '=';
          		buffer_index = (buffer_index+1) % BUFFER_SIZE;
       		}
       		if (key == '2')
       		{
          		buffer[buffer_index] = '"';
          		buffer_index = (buffer_index + 1) % BUFFER_SIZE;
       		}
       		if (key == '3')
       		{
         	 	buffer[buffer_index] = '#';
          		buffer_index = (bufferinde + 1) % BUFFER_SIZE;
       		}
       		if (key == '4')
       		{
         		 buffer[buffer_index] = '$';
          		buffer_index = (bufferinde + 1) % BUFFER_SIZE;
       		}
       		if (key == '5')
       		{
         	 	buffer[buffer_index] = '%';
          		buffer_index = (bufferinde + 1) % BUFFER_SIZE;
       		}
       		if (key == '6')
       		{
          		buffer[buffer_index] = '&';
          		buffer_index = (bufferinde + 1) % BUFFER_SIZE;
       		}
       		if (key == '7')
       		{
          		buffer[buffer_index] = '/';
          		buffer_index = (bufferinde + 1) % BUFFER_SIZE;
       		}
			 if (key == '8')
			 {
				  buffer[buffer_index] = '(';
          buffer_index = (buffer_index + 1) % BUFFER_SIZE;
			 }
			 if (key == '9')
			 {
				  buffer[buffer_index] = ')';
				  buffer_index = (buffer_index + 1) % BUFFER_SIZE;
			 }
			 if (key <= 'z' && key >= 'a')
			 {
				  buffer[buffer_index] = key - 'a' + 'A';
				  buffer_index = (buffer_index + 1) % BUFFER_SIZE;
			 }
			 if (key == '\n'|| key == '\b')
       {
          buffer[buffer_index] = key;
          buffer_index = (buffer_index + 1 ) % BUFFER_SIZE;
       }
       if (key == '1') //hotkey para cambiar el color de la hora
       {
          buffer[buffer_index] = '?';
          buffer_index = (buffer_index + 1) % BUFFER_SIZE;
       }
		  } else {
			 buffer[buffer_index] = key;
			 buffer_index = (buffer_index + 1) % BUFFER_SIZE;
      }
    }
}

char getBuffer(){
	if(index != buffer_index)
  {
		char aux = buffer[index];
		index = (index + 1) % BUFFER_SIZE;
    return aux;
  }
	return -1;
}
