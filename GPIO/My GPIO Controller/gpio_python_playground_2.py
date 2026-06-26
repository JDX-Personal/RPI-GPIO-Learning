#!/usr/bin/python
import GPIO_Controller_Class as gpio

btn = gpio.GPIO(27)

if btn.waitForEdge(1, 5000):
	print("Button was pressed!")
else:
	print("Timeout - no press detected")
