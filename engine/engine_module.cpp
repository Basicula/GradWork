#include <pybind11/pybind11.h>

#include <math_py.hpp>
#include <primitives_py.hpp>

PYBIND11_MODULE(engine, m)
{
    AddMathSubmodule(m);
    //AddPrimitivesSubModule(m);
}