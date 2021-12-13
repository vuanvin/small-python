#ifndef Py_DICTOBJECT_H
#define Py_DICTOBJECT_H

#include <map>
#include "object.h"

typedef struct _dictobject {
  PyObject_HEAD
  std::map<PyObject*, PyObject*> dict;
} PyDictObject;

PyAPI_FUNC(PyObject*) PyDict_Create();
PyAPI_DATA(PyTypeObject) PyDict_Type;

#endif /* Py_DICTOBJECT_H */