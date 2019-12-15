#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <math_py.hpp>
#include <visual_py.hpp>
#include <primitives_py.hpp>
#include <scene_module_py.hpp>

PYBIND11_MODULE(engine, m)
  {
  AddMathSubmodule(m);
  AddVisualSubmodule(m);
  AddPrimitivesSubmodule(m);
  AddSceneSubmodule(m);
  }