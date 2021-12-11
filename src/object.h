#ifndef Py_OBJECT_H
#define Py_OBJECT_H

typedef int Py_ssize_t;
typedef struct _typeobject PyTypeObject;

#define PyObject_HEAD   \
  Py_ssize_t ob_refcnt; \
  _typeobject *ob_type

#define PyObject_VAR_HEAD PyVarObject ob_base;

#define PyObject_HEAD_INIT(type) {1, type},
#define PyVarObject_HEAD_INIT(type, size) {PyObject_HEAD_INIT(type) size},

typedef struct _object {
  Py_ssize_t ob_refcnt;
  PyTypeObject *ob_type;
} PyObject;

typedef struct {
  PyObject ob_base;
  Py_ssize_t ob_size; /* Number of items in variable part */
} PyVarObject;

typedef Py_ssize_t Py_hash_t;
typedef PyObject *(*reprfunc)(PyObject *);
typedef Py_hash_t (*hashfunc)(PyObject *);

typedef PyObject *(*unaryfunc)(PyObject *);
typedef PyObject *(*binaryfunc)(PyObject *, PyObject *);
typedef PyObject *(*ternaryfunc)(PyObject *, PyObject *, PyObject *);

typedef struct {
  binaryfunc nb_add;
  binaryfunc nb_subtract;
  binaryfunc nb_multiply;
  binaryfunc nb_remainder;
  binaryfunc nb_divmod;
  unaryfunc nb_negative;
  unaryfunc nb_positive;
} PyNumberMethods;

typedef struct _typeobject {
  PyObject_VAR_HEAD
  const char *tp_name;
  PyNumberMethods *tp_as_number;
  hashfunc tp_hash;
  reprfunc tp_repr;
} PyTypeObject;

typedef int digit;

PyTypeObject PyType_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  "type",
  0,
  0,
  0
};

#endif /* Py_OBJECT_H */
