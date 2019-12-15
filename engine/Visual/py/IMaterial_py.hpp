#include <IMaterial.h>

namespace
  {
  class PyIMaterial : IMaterial
    {
    using IMaterial::IMaterial;
    };
  }

static void AddIMaterial(py::module& io_module)
  {
  py::class_<IMaterial, PyIMaterial>(io_module, "IMaterial");
  }