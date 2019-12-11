#include <Color.h>

namespace py = pybind11;

namespace
  {
  std::string hex_by_color_rgb(const Color& i_color)
    {
    char hex[10];
    sprintf(hex+2,"%x",i_color.GetRGB());
    hex[0] = '0';
    hex[1] = 'x';
    return std::string(hex);
    }
  }

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
        .def_property("red", &Color::GetRed, &Color::SetRed)
        .def_property("green", &Color::GetGreen, &Color::SetGreen)
        .def_property("blue", &Color::GetBlue, &Color::SetBlue)
        .def_property("rgb", &Color::GetRGB, &Color::SetRGB)
        .def("__repr__", [](const Color& i_color) 
                              { 
                              return "rgb: (" + 
                                      std::to_string(i_color.GetRed())   + ", " + 
                                      std::to_string(i_color.GetGreen()) + ", " +
                                      std::to_string(i_color.GetBlue())  + ")"  ;
                              })
        .def("__hex__", hex_by_color_rgb)
        .def("__str__", hex_by_color_rgb);
}