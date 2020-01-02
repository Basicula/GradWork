#include <Image.h>

static void AddImage(py::module& io_module)
  {
  py::class_<Image>(io_module, "Image")
    .def(py::init<
      std::size_t, 
      std::size_t, 
      const Color&>(),
      py::arg("width"),
      py::arg("height"),
      py::arg("color") = Color(0))
    .def("getPixel", &Image::GetPixel)
    .def("setPixel", &Image::SetPixel)
    .def_property_readonly("width", &Image::GetWidth)
    .def_property_readonly("height", &Image::GetHeight)
    .def_property_readonly("data", &Image::GetData)
    .def_property_readonly("rawData", &Image::GetRawData)
    .def("__str__", &Image::AsString);
  }