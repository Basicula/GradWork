#include <BoundingBox_py.hpp>
#include <Intersection_py.hpp>
#include <IObject_py.hpp>

static void AddCommonSubmodule(py::module& io_module)
  {
  auto common_submodule = io_module.def_submodule("Common");
  AddBoundingBox(common_submodule);
  AddIntersection(common_submodule);
  AddIObject(common_submodule);
  }