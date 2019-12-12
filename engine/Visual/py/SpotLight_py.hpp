#include <SpotLight.h>

namespace py = pybind11;

namespace
  {
  static void AddSpotLight(py::module io_module)
    {
    py::class_<SpotLight>(io_module,"SpotLight")
      .def(py::init<Vector3d, 
                    Color, 
                    double>(),
                    py::arg("location"),
                    py::arg("color") = Color(255,255,255),
                    py::arg("intensity") = 1.0)
      .def_property("location",
                    &SpotLight::GetLocation,
                    &SpotLight::SetLocation)
      .def_property("color",
                    &SpotLight::GetColor,
                    &SpotLight::SetColor)
      .def_property("intensity",
                    &SpotLight::GetIntensity,
                    &SpotLight::SetIntensity);
    }
  }

static void AddLight(py::module& io_module)
{
  auto light_module = io_module.def_submodule("Light");
  AddSpotLight(light_module);
}