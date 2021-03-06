#include <Python.h>

#include "AceD.h"

static PyObject *AceD_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    AceD_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    AceD_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef AceDMethods[] = {
    { "getPoWHash", AceD_getpowhash, METH_VARARGS, "Returns the proof of work hash using AceD hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef AceDModule = {
    PyModuleDef_HEAD_INIT,
    "AceD_hash",
    "...",
    -1,
    AceDMethods
};

PyMODINIT_FUNC PyInit_AceD_hash(void) {
    return PyModule_Create(&AceDModule);
}

#else

PyMODINIT_FUNC initAceD_hash(void) {
    (void) Py_InitModule("AceD_hash", AceDMethods);
}
#endif
