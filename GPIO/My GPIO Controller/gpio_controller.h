#pragma once
#include<gpiod.h>

enum GPIO_DIRECTION{ INPUT, OUTPUT };
enum GPIO_VALUE{ LOW=0, HIGH=1};
enum GPIO_EDGE{ NONE, RISING, FALLING, BOTH };

class GPIO{
	private:
		int gpioNumber;
		gpiod_chip* chip;
		gpiod_line* line;
		virtual void openLine();
		virtual void closeLine();
		virtual void requestLineOutput();
		virtual void requestLineInput();
	public:
		GPIO(int gpioNumber);
		virtual void setHigh();
		virtual void setLow();
		virtual int getValue();
		virtual void flash(int cycles);
		virtual void displayState();
		virtual ~GPIO();
	
};
