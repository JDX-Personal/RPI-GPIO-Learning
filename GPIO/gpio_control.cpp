/**
 * @file gpio_control.cpp
 * @brief Used to turn a GPIO on and off.  First argument is GPIO number.  Second argument is On or Off.
 * @author Jared Hagemann
 * @date 7/19/2026
 * */

#include<gpiod.h>
#include<iostream>
#include<string>
#include<cstring>

#define	CONSUMER	"Consumer"

int main(int argc, char* argv[]){	
	if(argc != 3){
		std::cout << "Must have exactly 2 arguments. First argument is GPIO number.  Second argument is On/Off\n";
		return 1;
	}
	
	//Need to check first argument still
	
	int status = 0;
	if(strcmp(argv[2], "On") == 0){
		status = 1;
	}
	else if(strcmp(argv[2] , "Off") == 0){
		status = 0;
	}
	else{
		std::cout << "Invalid second argument.  Must be either On or Off\n";
		return 1;
	}
	
	int line_num = std::stoi(argv[1]);	// GPIO Pin #4
	gpiod_chip* chip = gpiod_chip_open_by_name("gpiochip0"); 
	if (!chip) {
		std::cout << "Open chip failed\n";
		return 1;
	}
	
	gpiod_line* line = gpiod_chip_get_line(chip, line_num);
	if (!line) {
		std::cout << "Get line failed\n";
		gpiod_chip_close(chip);
		return 1;
	}
	
	int ret = gpiod_line_request_output(line, CONSUMER, status);
	if (ret < 0) {
		std::cout << "Request line as output failed\n";
		gpiod_line_release(line);
		gpiod_chip_close(chip);
		return 1;
	}
	
	//set value
	gpiod_line_set_value(line, status);	
	
	gpiod_line_release(line);
	gpiod_chip_close(chip);
	return 0;
}
