#pragma once
#include <cstdint>

struct gpiod_chip;
struct gpiod_line;

class GPIO{
	private:
		int gpioNumber = 0;
		gpiod_chip* chip = nullptr;
		gpiod_line* line = nullptr;
		bool isOutput = false;
		
		void openAndRequest(bool asOutput);
		void closeLine();
	public:
		explicit GPIO(int gpio);
		virtual ~GPIO();
		
		void setHigh();
		void setLow();
		int getValue();
		void flash(int cycles, int delay_us = 500000);
		void displayState();	
		
		GPIO(const GPIO&) = delete;
		GPIO& operator=(const GPIO&) = delete;
};
