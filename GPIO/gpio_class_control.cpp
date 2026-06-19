/**
 * @file gpio_class_control.cpp
 * @brief Uses a LED class to control multiple LEDs
 * @author Jared Hagemann
 * @date 7/19/2026
 * */
 
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<gpiod.h>

#define	CONSUMER	"Consumer"
#define FLASH_DELAY 1000000 //1 second

class LED{
	private:
		int gpioNumber;
		gpiod_chip* chip;
		gpiod_line* line;
		virtual void openLine();
		virtual void closeLine();
		virtual void requestLine();
	public:
		LED(int gpioNumber);
		virtual void turnOn();
		virtual void turnOff();
		virtual void displayState();
		virtual ~LED();
	
};



LED::LED(int gpioNumber){
	this->gpioNumber = gpioNumber;
}

LED::~LED(){}

void LED::openLine(){
	this->chip = gpiod_chip_open_by_name("gpiochip0"); 
	if (!this->chip) throw std::runtime_error("Open chip failed");
	
	this->line = gpiod_chip_get_line(chip, this->gpioNumber);
	if (!this->line){
		gpiod_chip_close(chip);
		throw std::runtime_error("Open line failed");
	}
}

void LED::closeLine(){
	gpiod_line_release(this->line);
	gpiod_chip_close(this->chip);
}

void LED::requestLine(){
	this -> openLine();
	int ret = gpiod_line_request_output(this->line, CONSUMER, 1);
	if (ret < 0) {
		gpiod_line_release(this->line);
		gpiod_chip_close(this->chip);
		throw std::runtime_error("Request line as output failed");
	}	
}

void LED::turnOn(){	
	//set value
	this -> requestLine();
	gpiod_line_set_value(this->line, 1);	
	this -> closeLine();
}

void LED::turnOff(){
	//set value
	this -> requestLine();
	gpiod_line_set_value(this->line, 0);	
	this -> closeLine();
}

void LED::displayState(){
	/*
	printf("Offset: %u, Name: %s, Consumer: %s, Direction: %d, Active State: %d, Bias: %d\n", 
                gpiod_line_offset(this->line), 
                gpiod_line_name(this->line),
                gpiod_line_consumer(this->line),
                gpiod_line_direction(this->line),
                gpiod_line_active_state(this->line),
                gpiod_line_bias(this->line));
    */
}



int main(){
	std::cout << "Starting GPIO Class Control Program\n";
	LED led1(4), led2(5);
	std::cout << "Flashing the LEDs for 5 seconds\n";
	for(int i = 0; i < 10; i++){
		led1.turnOn();
		led2.turnOff();
		usleep(FLASH_DELAY);
		led1.turnOff();
		led2.turnOn();
		usleep(FLASH_DELAY);
	}
	std::cout << "Finished GPIO Class Control Program\n";
	return 0;
}


