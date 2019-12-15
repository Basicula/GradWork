#include <SpotLight.h>

namespace
  {
  class PySpotLight : public SpotLight
    {
    using SpotLight::SpotLight;
    void SetState(bool i_state) override
      {
      PYBIND11_OVERLOAD(
        void,
        SpotLight,
        SetState,
        i_state);
      }
    bool GetState() const override
      {
      PYBIND11_OVERLOAD(
        bool,
        SpotLight,
        GetState,
        );
      }
    };
  }

static void AddSpotLight(py::module io_module)
  {
  py::class_<SpotLight, ILight, PySpotLight>(io_module, "SpotLight")
    .def(py::init<Vector3d,
      Color,
      double,
      bool>(),
      py::arg("location"),
      py::arg("color") = Color(255, 255, 255),
      py::arg("intensity") = 1.0,
      py::arg("state") = true)
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