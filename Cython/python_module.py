#!/usr/bin/python3
import ERPiModule
print("*** Start of the Python program")
print("--> Calling the C hello() function passing Jared")
ERPiModule.hello("Jared")
print("--> Calling the C integrate() function")
val = ERPiModule.integrate(0, 3.14159, 1000000)
print("*** The result is: ", val)
print("*** end of the Python program")
