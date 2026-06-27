#!/usr/bin/python
import GPIO_Controller_Class as gpio
import time

def on_edge(detected):
	if detected:
		print("Edge detected!")
	else:
		print("Timout or error")
		
led = gpio.GPIO(4);
button = gpio.GPIO(27);

button.waitForEdgeAsync(1, 20000, on_edge)

for i in range(20):
	led.setHigh()
	time.sleep(0.5)
	led.setLow()
	time.sleep(0.5)
	print(f"flash cycle {i + 1}")
