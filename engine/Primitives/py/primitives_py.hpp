#include <Ray_py.hpp>
#include <Intersection_py.hpp>

#include <IObject_py.hpp>
#include <Sphere_py.hpp>

static void AddPrimitivesSubmodule(py::module& io_module)
  {
  auto primitives_submodule = io_module.def_submodule("Primitives");
  AddRay(primitives_submodule);
  AddIntersection(primitives_submodule);

  AddIObject(primitives_submodule);
  AddSphere(primitives_submodule);
  }