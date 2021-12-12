#include "Python.h"
#include <cstdlib>
#include <string>

PyObject* PyInt_Create(int value) {
  PyIntObject* object = new PyIntObject;
  Py_REFCNT(object) = 1;
  Py_TYPE(object) = &PyInt_Type;
  object->ob_digit[0] = value;
  return (PyObject*) object;
}

static PyObject* int_repr(PyObject* _object) {
  PyIntObject *object = (PyIntObject*) _object;
  std::string str = std::to_string(object->ob_digit[0]);
  PyObject *result = PyStr_Create(str.c_str());

  return (PyObject*) object;
}


static PyObject *int_add(PyIntObject *left, PyIntObject *right) {
  PyIntObject *leftInt = (PyIntObject*) left;
  PyIntObject *rightInt = (PyIntObject*) right;
  PyIntObject *result = (PyIntObject*) PyInt_Create(0);
  if (result == nullptr) {
    std::exit(1);
  } else {
    result->ob_digit[0] = leftInt->ob_digit[0] + rightInt->ob_digit[0];
  }

  return (PyObject*) result;
}

static PyObject *int_substract(PyObject *left, PyObject *right) {
  PyIntObject *leftInt = (PyIntObject*) left;
  PyIntObject *rightInt = (PyIntObject*) right;
  PyIntObject *result = (PyIntObject*) PyInt_Create(0);
  if (result == nullptr) {
    std::exit(1);
  } else {
    result->ob_digit[0] = leftInt->ob_digit[0] - rightInt->ob_digit[0];
  }

  return (PyObject*) result;
}

static PyNumberMethods int_as_number = {
  .nb_add = (binaryfunc) int_add,
  .nb_subtract = 0,
  .nb_multiply = 0,
  .nb_remainder = 0,
  .nb_divmod = 0,
  .nb_negative = 0,
  .nb_positive = 0
};

static Py_hash_t int_hash(PyObject* _object) {
  return (Py_hash_t) ((PyIntObject*) _object)->ob_digit[0];
}

PyTypeObject PyInt_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  .tp_name = "int",
  .tp_as_number = &int_as_number,
  .tp_hash = int_hash,
  .tp_repr = int_repr,
  .tp_new = 0,
  .tp_del = 0
};