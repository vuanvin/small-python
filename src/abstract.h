#include "object.h"

void PyObject_Print(PyObject *object);
PyObject * PyObject_GetItem(PyObject *o, PyObject *key);
int PyObject_SetItem(PyObject *o, PyObject *key, PyObject *value);
int PyObject_DelItem(PyObject *o, PyObject *key);