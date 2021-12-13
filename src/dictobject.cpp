#include "Python.h"
#include <utility>
#include <string>
#include <map>


PyObject* PyDict_Create() {
    PyDictObject *object = new PyDictObject;
    Py_REFCNT(object) = 1;
    Py_TYPE(object) = &PyDict_Type;
    return (PyObject*) object;
}

static Py_hash_t dict_hash(PyObject* object) {
    return 100;
}

static PyObject* dict_add(PyDictObject* left, PyDictObject* right) {
    PyDictObject *result = (PyDictObject*) PyDict_Create();

    for (auto& item : left->dict) {
        auto m = Py_TYPE(result)->tp_as_mapping;
        m->mp_ass_subscript((PyObject*) result, item.first, item.second);
    }

    for (auto& item : right->dict) {
        auto m = Py_TYPE(result)->tp_as_mapping;
        m->mp_ass_subscript((PyObject*) result, item.first, item.second);
    }

    return (PyObject*)result;
}

Py_ssize_t dict_length(PyObject* object) {
  PyDictObject *dictObject = (PyDictObject*) object;
  return (Py_ssize_t) dictObject->dict.size();
}

PyObject *dict_subscript(PyDictObject *mp, PyObject *key) {
    auto& dict = mp->dict;
    auto it = dict.find(key);
    if (it == dict.end()) {
        return nullptr;
    }
    return it->second;
}

int PyDict_DelItem(PyObject *op, PyObject *key) {
    PyDictObject *mp;
    mp = (PyDictObject *)op;
    return mp->dict.erase(key);
}

int PyDict_SetItem(PyObject *op, PyObject *key, PyObject *value) {
    PyDictObject *mp;
    mp = (PyDictObject *)op;
    for (auto & item : mp->dict) {
        auto k = item.first;
        // 暂时使用Hash值判断是否相等，但这是不安全的。
        if (Py_TYPE(k) == Py_TYPE(key)) {
            auto t = Py_TYPE(k);
            if(t->tp_hash(k) == t->tp_hash(key)) {
                mp->dict[k] = value;
                key == nullptr;
            }
        }
    }

    if (key)
        mp->dict[key] = value;

    return 1;
}

static int
dict_ass_sub(PyDictObject *mp, PyObject *v, PyObject *w) {
    if (w == nullptr)
        return PyDict_DelItem((PyObject *)mp, v);
    else
        return PyDict_SetItem((PyObject *)mp, v, w);
}

static PyMappingMethods dict_as_mapping = {
    (lenfunc)dict_length, /*mp_length*/
    (binaryfunc)dict_subscript, /*mp_subscript*/
    (objobjargproc)dict_ass_sub, /*mp_ass_subscript*/
};

static PyNumberMethods dict_as_number = {
  .nb_add = (binaryfunc) dict_add,
  .nb_subtract = 0,
  .nb_multiply = 0,
  .nb_remainder = 0,
  .nb_divmod = 0,
  .nb_negative = 0,
  .nb_positive = 0
};

static PyObject* dict_repr(PyDictObject *object) {
    std::string str;
    str += "{";
    bool is_first = true;
    for (auto &item : object->dict) {
        auto keyStr = (PyStringObject*) Py_TYPE(item.first)->tp_repr(item.first);
        auto valueStr = (PyStringObject*) Py_TYPE(item.second)->tp_repr(item.second);
        if (is_first) {
            is_first = false;
        } else {
            str += ", ";
        }
        str += keyStr->value;
        str += " : ";
        str += valueStr->value;
    }
    str += "}\n";

    PyObject *result = PyStr_Create(str.c_str());
    return result;
}

PyTypeObject PyDict_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  .tp_name = "dict",
  .tp_as_number = &dict_as_number,
  .tp_as_mapping = &dict_as_mapping,
  .tp_hash = dict_hash,
  .tp_repr = (reprfunc) dict_repr,
  .tp_new = 0
};