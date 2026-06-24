#include <Python.h>
#include <math.h>

static PyObject* hello(PyObject* self, PyObject* args){
	const char* name;
	if(!PyArg_ParseTuple(args, "s", &name)){
		printf("Failed to parse the string name!\n");
		Py_RETURN_NONE;
	}
	printf("Hello %s!\n", name);
	Py_RETURN_NONE;
}


static PyObject* integrate(PyObject* self, PyObject* args){
	double a, b, dx, sum=0;
	int N;
	
	if(!PyArg_ParseTuple(args, "ddi", &a, &b, &N)){
		printf("Failed to parse the arguments!\n");
		Py_RETURN_NONE;
	}
	dx = (b-a)/N;
	for(int i=0; i<N; i++){
		sum += sin((a+i)*dx);
	}
	return Py_BuildValue("d", sum*dx);
}

static PyMethodDef ERPiMethods[] = {
	{"hello", hello, METH_VARARGS, "Displays Hello Derek!"},
	{"integrate", integrate, METH_VARARGS, "Integrates the sin(x) fn."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"ERPiModule",
	"Module for Exploring RPi",
	-1,
	ERPiMethods,
	NULL,
	NULL,
	NULL,
	NULL,
};

PyMODINIT_FUNC PyInit_ERPiModule(void){
	return PyModule_Create(&moduledef);
}
