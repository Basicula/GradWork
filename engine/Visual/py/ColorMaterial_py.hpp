#include <ColorMaterial.h>

namespace
  {
  class PyColorMaterial : public ColorMaterial
    {
    using ColorMaterial::ColorMaterial;
    std::string Serialize() const override
      {
      PYBIND11_OVERLOAD(
        std::string,
        ColorMaterial,
        Serialize,
        );
      }
    Color GetPrimitiveColor() const override
      {
      PYBIND11_OVERLOAD(
        Color,
        ColorMaterial,
        GetPrimitiveColor,
        );
      }
    Color GetLightInfluence(
      const Vector3d& i_point,
      const Vector3d& i_normal,
      std::shared_ptr<ILight> i_light) const override
      {
      PYBIND11_OVERLOAD_PURE(
        Color,
        ColorMaterial,
        GetLightInfluence,
        i_light
      );
      }
    Color GetMultiLightInfluence(
      const Vector3d& i_point,
      const Vector3d& i_normal, 
      const std::vector<std::shared_ptr<ILight>>& i_lights) const override
      {
      PYBIND11_OVERLOAD_PURE(
        Color,
        ColorMaterial,
        GetMultiLightInfluence,
        i_lights
      );
      }
    };
  }

static void AddColorMaterial(py::module& io_module)
  {
  py::class_<ColorMaterial, std::shared_ptr<ColorMaterial>, IMaterial, PyColorMaterial>(io_module, "ColorMaterial")
    .def(py::init<Color,
      Vector3d,
      Vector3d,
      Vector3d,
      double,
      double,
      double>(),
      py::arg("color"),
      py::arg("ambient") = Vector3d(1.0, 1.0, 1.0),
      py::arg("diffuse") = Vector3d(1.0, 1.0, 1.0),
      py::arg("specular") = Vector3d(1.0, 1.0, 1.0),
      py::arg("shinines") = 1.0,
      py::arg("reflection") = 0.0,
      py::arg("refraction") = 0.0)
    .def_property("color",
      &ColorMaterial::GetColor,
      &ColorMaterial::SetColor)
    .def_property("ambient",
      &ColorMaterial::GetAmbient,
      &ColorMaterial::SetAmbient)
    .def_property("diffuse",
      &ColorMaterial::GetDiffuse,
      &ColorMaterial::SetDiffuse)
    .def_property("specular",
      &ColorMaterial::GetSpecular,
      &ColorMaterial::SetSpecular)
    .def_property("reflection",
      &ColorMaterial::GetReflection,
      &ColorMaterial::SetReflection)
    .def_property("refraction",
      &ColorMaterial::GetRefraction,
      &ColorMaterial::SetRefraction)
    .def_property("shinines",
      &ColorMaterial::GetShinines,
      &ColorMaterial::SetShinines)
    .def("acolor", &ColorMaterial::GetAmbientColor)
    .def("dcolor", &ColorMaterial::GetDiffuseColor)
    .def("scolor", &ColorMaterial::GetSpecularColor);
  }