#include "object.h"

PyTypeObject PyType_Type = {
  PyVarObject_HEAD_INIT(&PyType_Type, 0)
  "type",
  0,
  0,
  0
};
