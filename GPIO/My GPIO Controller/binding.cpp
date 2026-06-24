#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include "gpio_controller.h"
#include<boost/python.hpp>
#include <iterator>

BOOST_PYTHON_MODULE(gpio_controller){
	boost::python::class_<GPIO>("GPIO",boost::python::init<int>())
		.def("setHigh", &GPIO::setHigh)
		.def("setLow", &GPIO::setLow)
		.def("getValue", &GPIO::getValue)
		.def("flash", &GPIO::flash)
		.def("displayState", &GPIO::displayState);
}
