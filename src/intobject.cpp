#include "intobject.h"
#include <cstdlib>

typedef struct _intobject {
  PyVarObject ob_base;
  digit ob_digit[1];
} PyIntObject;

PyObject* PyInt_Create(int value) {
  PyIntObject* object = new PyIntObject;
  object->ob_base.ob_base.ob_refcnt = 1;
  object->ob_base.ob_base.ob_type = &PyInt_Type;
  object->ob_digit[0] = value;
  return (PyObject*) object;
}

static PyObject* int_repr(PyObject* _object) {

}

static PyObject *int_add(PyObject *left, PyObject *right) {
  PyIntObject *leftInt = (PyIntObject*) left;
  PyIntObject *rightInt = (PyIntObject*) right;
  PyIntObject *result = (PyIntObject*) PyInt_Create(0);
  if (result == nullptr) {
    std::exit(1);
  } else {
    result->ob_digit[0] = leftInt->ob_digit[0] + rightInt->ob_digit[0];
  }
}

static PyNumberMethods int_as_number = {
  (binaryfunc) int_add,
  0,
  0,
  0,
  0,
  0,
  0
};

static Py_hash_t int_hash(PyObject* _object) {
  return (Py_hash_t) ((PyIntObject*) _object)->ob_digit[0];
}

PyTypeObject PyInt_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  "int",
  &int_as_number,
  int_hash,
  int_repr
};
