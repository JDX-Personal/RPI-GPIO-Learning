#!/bin/bash
g++ -O3 binding.cpp gpio_controller.cpp -shared -I/usr/include/python3.9/ -lpython3.9 -lboost_python39 -lgpiod -o gpio_controller.so
#Use the following to fin the location of boost_python
#find /usr -name '*boost_python*' 2>/dev/null
