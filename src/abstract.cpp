#include "Python.h"
#include <iostream>

void PyObject_Print(PyObject *object) {
    if (Py_TYPE(object) != &PyString_Type) {
        object = Py_TYPE(object)->tp_repr(object);
    }
    std::cout << ((PyStringObject*) object)->value << std::endl;
}

PyObject *
PyObject_GetItem(PyObject *o, PyObject *key) {
    PyMappingMethods *m;
    PySequenceMethods *ms;

    if (o == nullptr || key == nullptr) {
        return nullptr;
    }

    m = Py_TYPE(o)->tp_as_mapping;
    if (m && m->mp_subscript) {
        PyObject *item = m->mp_subscript(o, key);
        return item;
    }

    return nullptr;
}

int PyObject_SetItem(PyObject *o, PyObject *key, PyObject *value) {
    PyMappingMethods *m;

    m = Py_TYPE(o)->tp_as_mapping;
    if (m && m->mp_ass_subscript)
        return m->mp_ass_subscript(o, key, value);

    return 0;
}

int
PyObject_DelItem(PyObject *o, PyObject *key)
{
    PyMappingMethods *m;

    m = Py_TYPE(o)->tp_as_mapping;
    if (m && m->mp_ass_subscript)
        return m->mp_ass_subscript(o, key, nullptr);
}
