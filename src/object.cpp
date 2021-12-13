#include "object.h"

void _Py_Dealloc(PyObject *op) {
    destructor dealloc = Py_TYPE(op)->tp_dealloc;
    (*dealloc)(op);
}