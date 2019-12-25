#include <IMaterial.h>

namespace
  {
  class PyIMaterial : IMaterial
    {
    using IMaterial::IMaterial;
    std::string Serialize() const override
      {
      PYBIND11_OVERLOAD_PURE(
        std::string,
        IMaterial,
        Serialize,
        );
      }
    Color GetPrimitiveColor() const override
      {
      PYBIND11_OVERLOAD_PURE(
        Color,
        IMaterial,
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
        IMaterial,
        GetLightInfluence,
        i_point,
        i_normal,
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
        IMaterial,
        GetMultiLightInfluence,
        i_point,
        i_normal,
        i_lights
        );
      }
    };
  }

static void AddIMaterial(py::module& io_module)
  {
  py::class_<IMaterial, std::shared_ptr<IMaterial>, PyIMaterial>(io_module, "IMaterial")
    .def("primitiveColor", &IMaterial::GetPrimitiveColor)
    .def("lightInfluence", &IMaterial::GetLightInfluence)
    .def("multiLightInfluence", &IMaterial::GetMultiLightInfluence)
    .def("__repr__", &IMaterial::Serialize);
  }