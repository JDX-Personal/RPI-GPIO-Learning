#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include "GPIO_Controller_Class.h"
#include<boost/python.hpp>
#include <stdexcept>

namespace py = boost::python;

void translateRuntimeError(const std::runtime_error& e){
	PyErr_SetString(PyExc_RuntimeError, e.what());
}

BOOST_PYTHON_MODULE(GPIO_Controller_Class){
	py::register_exception_translator<std::runtime_error>(&translateRuntimeError);
	
	py::class_<GPIO, boost::noncopyable>("GPIO", py::init<int>())
		.def("setHigh", &GPIO::setHigh)
		.def("setLow", &GPIO::setLow)
		.def("getValue", &GPIO::getValue)		
		.def("displayState", &GPIO::displayState)
		.def("flash", 
				&GPIO::flash,
				(py::arg("cycles"), py::arg("delay_us") = 500000))
		.def("waitForEdge", 
				&GPIO::waitForEdge,
				(py::arg("eventType"), py::arg("timeout_ms") = -1))
		.def("waitForEdgeAsync", &GPIO::waitForEdgeAsync)
	;
}
