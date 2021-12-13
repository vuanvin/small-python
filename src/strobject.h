#ifndef Py_STROBJECT_H
#define Py_STROBJECT_H

#include "object.h"

typedef struct _strobject {
  PyObject_HEAD
  Py_hash_t hash_value;
  Py_ssize_t length;
  char value[50];
} PyStringObject;

PyAPI_DATA(PyTypeObject) PyString_Type;
PyAPI_FUNC(PyObject*) PyStr_Create(const char* value);

#endif /* Py_STROBJECT_H */