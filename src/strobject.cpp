#include "Python.h"
#include <string>
#include <cstring>

PyObject *PyStr_Create(const char* value) {
  PyStringObject *object = new PyStringObject;
  Py_REFCNT(object) = 1;
  Py_TYPE(object) = &PyString_Type;
  object->length = (value == nullptr) ? 0 : strlen(value);
  object->hash_value = -1;
  memset(object->value, 0, 50);
  if (value) {
      strcpy(object->value, value);
  }

  return (PyObject*) object;
}

static PyObject* str_repr(PyStringObject *object) {
    return (PyObject*) object;
}

static Py_hash_t str_hash(PyObject* object) {
    PyStringObject *strObject = (PyStringObject*) object;
    register int len;
    register unsigned char *p;
    register long x;
    if (strObject->hash_value != -1) {
        return strObject->hash_value;
    }
    len = strObject->length;
    p = (unsigned char *) strObject->value;
    x = *p << 7;
    while (--len >= 0) {
        x = (1000003 * x) ^ *p++;
    }
    
    return x;
}

static PyObject* str_add(PyStringObject *left, PyStringObject *right) {
    PyStringObject *leftStr = (PyStringObject*) left;
    PyStringObject *rightStr = (PyStringObject*) right;
    PyStringObject *result = (PyStringObject*) PyStr_Create(nullptr);
    if (result == nullptr) {
        printf("We have no enough memory!!");
        exit(1);
    } else {
        strcpy(result->value, leftStr->value);
        strcat(result->value, rightStr->value);
    }
    return (PyObject*) result;
}

static PyNumberMethods str_as_number = {
  .nb_add = (binaryfunc) str_add,
  .nb_subtract = 0,
  .nb_multiply = 0,
  .nb_remainder = 0,
  .nb_divmod = 0,
  .nb_negative = 0,
  .nb_positive = 0
};

PyTypeObject PyString_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  .tp_name = "str",
  .tp_as_number = &str_as_number,
  .tp_hash = (hashfunc)str_hash,
  .tp_repr = (reprfunc)str_repr,
  .tp_new = 0
};