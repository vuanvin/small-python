#ifndef Py_INTOBJECT_H
#define Py_INTOBJECT_H

#include "object.h"
#include "pyport.h"

typedef unsigned digit;
typedef int sdigit; /* signed variant of digit */

typedef struct _intobject {
  PyVarObject ob_base;
  digit ob_digit[1];
} PyIntObject;

PyAPI_FUNC(PyObject*) PyInt_Create(int value);
PyAPI_DATA(PyTypeObject) PyInt_Type;

#endif /* Py_INTOBJECT_H */