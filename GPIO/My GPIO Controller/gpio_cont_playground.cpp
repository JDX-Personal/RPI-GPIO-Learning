/**
 * @file gpio_cont_playground.cpp
 * @brief Used for testing gpio_controller
 * @author Jared Hagemann
 * @date 7/22/2026
 * */

#include<iostream>
#include<unistd.h>
#include "gpio_controller.h"

int main(){
	GPIO gpio4(4), gpio27(27);
	
	for(int i=0; i<10; i++){
		gpio4.setHigh();
		usleep(500000);
		gpio4.setLow();
		usleep(500000);
	}
	
	std::cout << "The ouput state is: " << gpio27.getValue() << "\n";
	
	gpio4.flash(1000000);
}
