/**
 * @file gpio_control.cpp
 * @brief GPIO class to simplify GPIO control
 * @author Jared Hagemann
 * @date 7/22/2026
 * */
#include "gpio_controller.h"
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<gpiod.h>

#define	CONSUMER	"GPIO Controller Class"
#define FLASH_DELAY 1000000 //1 second



GPIO::GPIO(int gpioNumber){
	this->gpioNumber = gpioNumber;
}

GPIO::~GPIO(){}

void GPIO::openLine(){
	this->chip = gpiod_chip_open_by_name("gpiochip0"); 
	if (!this->chip) throw std::runtime_error("Open chip failed");
	
	this->line = gpiod_chip_get_line(chip, this->gpioNumber);
	if (!this->line){
		gpiod_chip_close(chip);
		throw std::runtime_error("Open line failed");
	}
}

void GPIO::closeLine(){
	gpiod_line_release(this->line);
	gpiod_chip_close(this->chip);
}

void GPIO::requestLineOutput(){
	this -> openLine();
	int ret = gpiod_line_request_output(this->line, CONSUMER, 1);
	if (ret < 0) {
		gpiod_line_release(this->line);
		gpiod_chip_close(this->chip);
		throw std::runtime_error("Request line as output failed");
	}	
}

void GPIO::requestLineInput(){
	this -> openLine();
	int ret = gpiod_line_request_input(this->line, CONSUMER);
	if (ret < 0) {
		gpiod_line_release(this->line);
		gpiod_chip_close(this->chip);
		throw std::runtime_error("Request line as input failed");
	}	
}

void GPIO::setHigh(){	
	//set value
	this -> requestLineOutput();
	gpiod_line_set_value(this->line, 1);	
	this -> closeLine();
}

void GPIO::setLow(){
	//set value
	this -> requestLineOutput();
	gpiod_line_set_value(this->line, 0);	
	this -> closeLine();
}

int GPIO::getValue(){
	//get value
	int value;
	this -> requestLineInput();
	value = gpiod_line_get_value(this->line);
	this -> closeLine();
	return value;
}

void GPIO::flash(int cycles){
	this -> requestLineOutput();
	for(int i=0; i < cycles; i++){
		gpiod_line_set_value(this->line, 1);
		gpiod_line_set_value(this->line, 0);	
	}
	this -> closeLine();
}

void GPIO::displayState(){	
	printf("Offset: %u, Name: %s, Consumer: %s, Direction: %d, Active State: %d, Bias: %d\n", 
                gpiod_line_offset(this->line), 
                gpiod_line_name(this->line),
                gpiod_line_consumer(this->line),
                gpiod_line_direction(this->line),
                gpiod_line_active_state(this->line),
                gpiod_line_bias(this->line));    
}

