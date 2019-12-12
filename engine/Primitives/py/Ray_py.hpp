#include <Ray.h>

static void AddRay(py::module& io_module)
  {
  py::class_<Ray>(io_module, "Ray")
      .def(py::init<Vector3d,Vector3d>())
      .def_property("origin",
                    &Ray::GetOrigin,
                    &Ray::SetOrigin)
      .def_property("direction",
                    &Ray::GetDirection,
                    &Ray::SetDirection);
  }