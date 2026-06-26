#!/usr/bin/python
# Uses the gpio_controller.so file to blink an LED until a button is pushed
import GPIO_Controller_Class
from time import sleep
print("Start of the Python program")
gpio4 = GPIO_Controller_Class.GPIO(4);
gpio27 = GPIO_Controller_Class.GPIO(27)
while gpio27.getValue() == 0:
	gpio4.setHigh()
	sleep(0.1)
	gpio4.setLow()
	sleep(0.1)
print("End of Python program")
