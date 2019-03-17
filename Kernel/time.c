#include <time.h>
#include <videoDriver.h>

static unsigned long ticks = 0;

void timerHandler() {
	ticks++;
	if ((tickCount() % 9) == 0)
	{
		blink();
	}
}

int tickCount() {
	return ticks;
}

int secondCount() {
	return ticks / 18;
}

void delay()
{
	int ticks;
	int finalTicks = tickCount() + 1;
	while(ticks = tickCount() != finalTicks)
	{

	}
}
