#include <BoundingBox.h>

static void AddBoundingBox(py::module& io_module)
  {
  py::class_<BoundingBox>(io_module, "BoundingBox")
    .def(py::init<>())
    .def_property_readonly("min", &BoundingBox::GetMin)
    .def_property_readonly("max", &BoundingBox::GetMax)
    .def("isValid", &BoundingBox::IsValid)
    .def("addPoint", &BoundingBox::AddPoint);
  }