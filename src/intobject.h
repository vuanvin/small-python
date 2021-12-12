#ifndef Py_INTOBJECT_H
#define Py_INTOBJECT_H

#include "object.h"

typedef struct _intobject {
  PyVarObject ob_base;
  digit ob_digit[1];
} PyIntObject;

typedef unsigned digit;
typedef int sdigit; /* signed variant of digit */

PyObject* PyInt_Create(int value);
PyTypeObject PyInt_Type;

#endif /* Py_INTOBJECT_H */