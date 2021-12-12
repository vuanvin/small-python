#ifndef Py_OBJECT_H
#define Py_OBJECT_H

typedef int Py_ssize_t;
typedef Py_ssize_t Py_hash_t;
typedef struct _typeobject PyTypeObject;

#define PyObject_HEAD             PyObject ob_base;
#define PyObject_VAR_HEAD         PyVarObject ob_base;
#define PyObject_HEAD_INIT(type) {1, type},
#define PyVarObject_HEAD_INIT(type, size) {PyObject_HEAD_INIT(type) size},

/* Cast argument to PyObject* type. */
#define _PyObject_CAST(op) ((PyObject*)(op))
#define _PyObject_CAST_CONST(op) ((const PyObject*)(op))

/* Cast argument to PyVarObject* type. */
#define _PyVarObject_CAST(op) ((PyVarObject*)(op))

#define Py_REFCNT(ob)           (_PyObject_CAST(ob)->ob_refcnt)
#define Py_TYPE(ob)             (_PyObject_CAST(ob)->ob_type)
#define Py_SIZE(ob)             (_PyVarObject_CAST(ob)->ob_size)



typedef struct _object {
  Py_ssize_t ob_refcnt;
  PyTypeObject *ob_type;
} PyObject;

typedef struct _varobject {
  PyObject_HEAD
  Py_ssize_t ob_size; /* Number of items in variable part */
} PyVarObject;


static inline void _Py_INCREF(PyObject *op) {
  op->ob_refcnt++;
}

typedef PyObject *(*reprfunc)(PyObject *);
typedef Py_hash_t (*hashfunc)(PyObject *);

typedef PyObject *(*unaryfunc)(PyObject *);
typedef PyObject *(*binaryfunc)(PyObject *, PyObject *);
typedef PyObject *(*ternaryfunc)(PyObject *, PyObject *, PyObject *);
typedef Py_ssize_t (*lenfunc)(PyObject *);
typedef int(*objobjargproc)(PyObject *, PyObject *, PyObject *);

typedef void (*destructor)(PyObject *);
typedef PyObject *(*newfunc)(PyTypeObject *, PyObject *, PyObject *);

typedef struct {
  binaryfunc nb_add;
  binaryfunc nb_subtract;
  binaryfunc nb_multiply;
  binaryfunc nb_remainder;
  binaryfunc nb_divmod;
  unaryfunc nb_negative;
  unaryfunc nb_positive;
} PyNumberMethods;

typedef struct {
    lenfunc sq_length;
    binaryfunc sq_concat;
} PySequenceMethods;

typedef struct {
    lenfunc mp_length;
    binaryfunc mp_subscript;
    objobjargproc mp_ass_subscript;
} PyMappingMethods;

typedef struct _typeobject {
  PyObject_VAR_HEAD
  const char *tp_name;

  PyNumberMethods *tp_as_number;
  PySequenceMethods *tp_as_sequence;
  PyMappingMethods *tp_as_mapping;

  hashfunc tp_hash;
  reprfunc tp_repr;
  newfunc tp_new;
  destructor tp_del;
  destructor tp_dealloc;
} PyTypeObject;

PyTypeObject PyType_Type;


#define Py_INCREF(op) _Py_INCREF(_PyObject_CAST(op))

void _Py_Dealloc(PyObject *op) {
    destructor dealloc = Py_TYPE(op)->tp_dealloc;
    (*dealloc)(op);
}

static inline void _Py_DECREF(PyObject *op) {
  if (--op->ob_refcnt == 0) {
    _Py_Dealloc(op);
  }
}

#define Py_DECREF(op) _Py_DECREF(_PyObject_CAST(op))

#endif /* Py_OBJECT_H */