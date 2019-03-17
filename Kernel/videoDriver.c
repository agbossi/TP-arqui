#include <videoDriver.h>
#include <font.h>

#define HEIGHT y_res
#define WIDTH x_res
#define MOUSE_LIMIT HEIGHT/CHAR_HEIGHT* WIDTH

typedef struct {
	unsigned char red, green, blue;
} colour;

static int x_res = 0;
static int y_res = 0;
static int terminal = 0;
static int initial_colour = 0;
static char buffer[2000] = { ' ' };
static unsigned char ** const VIDEO = (unsigned char**) 0x0005C28;
static int mousescreen = 0;
static int mousepixel = 0;
static int mouseindex = 0;

static colour letter = {175,238,238}; //TURQUESA
static colour number = {175,238,238}; //TURQUESA
static colour background = {0,0,0};
static int scrolling = 0;

void loadVideoDriver()
{
	x_res = setResolution((unsigned char *)0x0005C12);
	y_res = setResolution((unsigned char *)0x0005C14);
	mousescreen = MOUSE_LIMIT - WIDTH;
	mouseindex=mousescreen;
}

void setTerminal(int t)
{
	terminal=t;
	mousescreen= MOUSE_LIMIT - WIDTH +terminal;
}

static int setResolution(unsigned char *ptr)
{
	unsigned char *res_byte = ptr;
	int res = 0;
	res += *(res_byte + 1);
	res = res << 8;
	res += *res_byte;
	return res;
}

void getResolution(int* x,int*y)
{
	(*x)=HEIGHT;
	(*y)=WIDTH;
}

void scrollUp()
{
	memcpy(*VIDEO, *VIDEO + (3 * WIDTH * CHAR_HEIGHT), (HEIGHT * WIDTH * 3) - (CHAR_HEIGHT * WIDTH * 3));
	mousescreen= MOUSE_LIMIT - WIDTH;
	scrolling=1;
	for (int i = 0; i < WIDTH/CHAR_WIDTH; i++)
	{
		printChar(' ');
		buffer[i]=' ';
	}
	scrolling=0;
	mousescreen = MOUSE_LIMIT - WIDTH;
	mouseindex = MOUSE_LIMIT - WIDTH + terminal;
}

void eraseCharacter()
{
	if (mousescreen>MOUSE_LIMIT - WIDTH + terminal)
	{
		mousescreen--;
		putCharAt(' ',mousescreen+1);
		printChar(' ');
		mousescreen--;
		mouseindex--;
	}
}

void newLine()
{
	putCharAt(buffer[mousescreen],mousescreen);
	mousescreen += WIDTH -mousescreen%WIDTH;
	if(mousescreen>=MOUSE_LIMIT)
		scrollUp();
}

void printChar(char c)
{
	if(mousescreen%(WIDTH/CHAR_WIDTH) == 0 && mousescreen != MOUSE_LIMIT - WIDTH)
		newLine();
	if(mousescreen>=MOUSE_LIMIT)
		scrollUp();
	if(c=='\b')
	{
		eraseCharacter();
	}else if(c=='\n'){
		newLine();
		mouseindex= MOUSE_LIMIT - WIDTH;
	}else if (c > 31 || isNumber(c)){
		buffer[mousescreen] = c;
		putCharAt(c,mousescreen);
		mousescreen++;
		mouseindex++;
		if (!scrolling)
		{
			if(mousescreen%(WIDTH/CHAR_WIDTH) == 0 && mousescreen != MOUSE_LIMIT - WIDTH)
				newLine();
		}

	}
}

void moveCursorLeft()
{
	if (mousescreen>MOUSE_LIMIT - WIDTH + terminal)
	{
		mousescreen--;
		putCharAt(buffer[mousescreen+1],mousescreen+1);
	}
}

void moveCursorRight()
{
	if (mousescreen < mouseindex)
	{
		mousescreen++;
		putCharAt(buffer[mousescreen-1],mousescreen-1);
	}
}

static int isNumber(char c)
{
	return c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0';
}

static void alterColour(colour * letter)
{
	if(initial_colour == 0)
	{
		letter->red = 255;
		letter->green = 255;
		letter->blue = 255;
		initial_colour++;
		return;
	}else if(initial_colour == 1){
		letter->red = 255;
		letter->green = 0;
		letter->blue = 0;
		initial_colour++;
		return;
	}else if(initial_colour == 2){
		letter->red = 0;
		letter->green = 128;
		letter->blue = 128;
		initial_colour = 0;
		return;
	}
}

void putCharAt(char c,int index)
{
	int x=(index/WIDTH)*CHAR_HEIGHT;
	int y=(index%WIDTH)*CHAR_WIDTH;
	unsigned char * char_map = pixel_map(c);
	if(c == '?'){
		alterColour(&number);
		return;
	}
	for(int i = 0; i < CHAR_HEIGHT; i++)
	{
		unsigned char pixel = char_map[i];
		char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
		char aux;
		for (int j = 0; j < CHAR_WIDTH; j++)
		{
			aux = pixel & mask[j];
			unsigned char * pixcolour = (*VIDEO) + 3 * ((y+j)+(x+i)*WIDTH);
			if (aux != 0)
			{
				if(isNumber(c) || c == ':')
				{
					pixcolour[0] = number.blue;
					pixcolour[1] = number.green;
					pixcolour[2] = number.red;
				} else {
					pixcolour[0] = letter.blue;
					pixcolour[1] = letter.green;
					pixcolour[2] = letter.red;
				}
			} else {
				pixcolour[0] = 0;
				pixcolour[1] = 0;
				pixcolour[2] = 0;
			}
		}
	}
}

void blink()
{
	int x=(mousescreen/WIDTH)*CHAR_HEIGHT;
	int y=(mousescreen%WIDTH)*CHAR_WIDTH;
	for (int i = 0; i < CHAR_HEIGHT; i++)
	{
		for (int j = 0; j < CHAR_WIDTH; j++)
		{
			unsigned char * pixcolour = (*VIDEO) + 3 * ((y+j)+(x+i)*WIDTH);

			if(pixcolour[0] == letter.blue){
				pixcolour[0] = 0;
			}else{
				pixcolour[0] = letter.blue;
			}
			if(pixcolour[1] == letter.green){
				pixcolour[1] = 0;
			}else{
				pixcolour[1] = letter.green;
			}
			if(pixcolour[2] == letter.red){
				pixcolour[2] = 0;
			}else{
				pixcolour[2] = letter.red;
			}
		}
	}
}

void putPixelAt(int colour,int x,int y)
{
	if (y < WIDTH && x < HEIGHT - CHAR_HEIGHT){
		unsigned char * pixcolour = (*VIDEO) + 3 * (y + x * WIDTH);
		if (colour == 1) {
			pixcolour[0] = letter.blue;
			pixcolour[1] = letter.green;
			pixcolour[2] = letter.red;
		} else {
			pixcolour[0] = 0;
			pixcolour[1] = 0;
			pixcolour[2] = 0;
		}
	}
}

void printDec(uint64_t value)
{
	printBase(value, 10);
}

void printHex(uint64_t value)
{
	printBase(value, 16);
}

void printBin(uint64_t value)
{
	printBase(value, 2);
}

void printBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    printString(buffer);
}
void printString(const char * string)
{
	int i;
	for (i = 0; string[i] != 0; i++)
	{
		printChar(string[i]);
	}
}

void clearScreen()
{
	for (int i = 0; i < HEIGHT/CHAR_HEIGHT; i++)
	{
		newLine();
	}
	mousescreen = MOUSE_LIMIT - WIDTH + terminal;
}

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;
	do{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}	while (value /= base);
	*p = 0;
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	return digits;
}
