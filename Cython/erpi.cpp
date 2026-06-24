#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include<string>
#include<boost/python.hpp>
#include <iterator>
using namespace std;
namespace exploringrpi{
	string hello(string name){
		return ("Hello " + name + "!");
	}
	
	double integrate (double a , double b, int n){
		double sum=0, dx = (b-a)/n;
		for(int i=0; i<n; i++){ sum += sin((a+i)*dx); }
		return sum*dx;
	}
	
	BOOST_PYTHON_MODULE(erpi){
		using namespace boost::python;
		def("hello",hello);
		def("integrate",integrate);
	}
}
