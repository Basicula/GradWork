#include <Color.h>

namespace py = pybind11;

static void AddColor(py::module& io_module)
{
    py::class_<Color>(io_module,"Color")
        .def(py::init<>())
        .def(py::init<uint>())
        .def(py::init<uchar,uchar,uchar>())
        .def(py::self * double())
        .def(py::self * Vector3d())
        .def(py::self + py::self)
        .def(py::self == py::self)
        .def(py::self != py::self)
        .def("red", &Color::Red)
        .def("green", &Color::Green)
        .def("blue", &Color::Blue);
}