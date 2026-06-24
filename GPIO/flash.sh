#!/bin/bash
echo "Starting Script"
COUNTER=0
while [ $COUNTER -lt 10000 ]; do
	gpioset gpiochip0 4=1
	let COUNTER=COUNTER+1
	#sleep 1
	gpioset gpiochip0 4=0
	#sleep 1
done
echo "End Script"