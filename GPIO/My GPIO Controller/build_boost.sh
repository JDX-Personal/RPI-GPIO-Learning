#!/bin/bash
g++ -O3 binding.cpp GPIO_Controller_Class.cpp -shared -I/usr/include/python3.9/ -lpython3.9 -lboost_python39 -lgpiod -o GPIO_Controller_Class.so
#Use the following to fin the location of boost_python
#find /usr -name '*boost_python*' 2>/dev/null
