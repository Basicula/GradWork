#include <SpotLight.h>

namespace
  {
  class PySpotLight : public SpotLight
    {
    using SpotLight::SpotLight;
    };
  }

static void AddSpotLight(py::module io_module)
  {
  py::class_<SpotLight, ILight, PySpotLight>(io_module, "SpotLight")
    .def(py::init<Vector3d,
      Color,
      double>(),
      py::arg("location"),
      py::arg("color") = Color(255, 255, 255),
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