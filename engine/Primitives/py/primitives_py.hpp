#include <Ray_py.hpp>

static void AddPrimitivesSubmodule(py::module& io_module)
  {
  auto primitives_submodule = io_module.def_submodule("Primitives");
  AddRay(primitives_submodule);
  }