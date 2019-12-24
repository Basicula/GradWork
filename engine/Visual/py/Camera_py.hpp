#include <Camera.h>

static void AddCamera(py::module& io_module)
  {
  py::class_<Camera>(io_module, "Camera")
    .def(py::init<
      const Vector3d&,
      const Vector3d&,
      const Vector3d&,
      double,
      double,
      double>())
    .def_property("location",
      &Camera::GetLocation,
      &Camera::SetLocation)
    .def("direction", &Camera::GetDirection)
    .def("__repr__", &Camera::Serialize);
  }