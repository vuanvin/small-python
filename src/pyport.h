#ifndef Py_PYPORT_H
#define Py_PYPORT_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #define Py_IMPORTED_SYMBOL __declspec(dllimport)
    #define Py_EXPORTED_SYMBOL __declspec(dllexport)
    #define Py_LOCAL_SYMBOL
#else
/*
 * If we only ever used gcc >= 5, we could use __has_attribute(visibility)
 * as a cross-platform way to determine if visibility is supported. However,
 * we may still need to support gcc >= 4, as some Ubuntu LTS and Centos versions
 * have 4 < gcc < 5.
 */
    #ifndef __has_attribute
      #define __has_attribute(x) 0  // Compatibility with non-clang compilers.
    #endif
    #if (defined(__GNUC__) && (__GNUC__ >= 4)) ||\
        (defined(__clang__) && __has_attribute(visibility))
        #define Py_IMPORTED_SYMBOL __attribute__ ((visibility ("default")))
        #define Py_EXPORTED_SYMBOL __attribute__ ((visibility ("default")))
        #define Py_LOCAL_SYMBOL  __attribute__ ((visibility ("hidden")))
    #else
        #define Py_IMPORTED_SYMBOL
        #define Py_EXPORTED_SYMBOL
        #define Py_LOCAL_SYMBOL
    #endif
#endif

/* If no external linkage macros defined by now, create defaults */
#ifndef PyAPI_FUNC
#       define PyAPI_FUNC(RTYPE) Py_EXPORTED_SYMBOL RTYPE
#endif
#ifndef PyAPI_DATA
#       define PyAPI_DATA(RTYPE) extern Py_EXPORTED_SYMBOL RTYPE
#endif

#endif /* Py_PYPORT_H */