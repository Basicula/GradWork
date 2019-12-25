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
    };
  }

static void AddIMaterial(py::module& io_module)
  {
  py::class_<IMaterial, std::shared_ptr<IMaterial>, PyIMaterial>(io_module, "IMaterial")
    .def("__repr__", &IMaterial::Serialize);
  }