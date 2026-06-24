#!/usr/bin/python
#A Python program that calls C program code
import erpi
print("Start of the Python program")
print(erpi.hello("Jared"))
val = erpi.integrate(0, 3.14159, 1000000)
print("the integral result is: ", val)
print("end of the Python program")
