#include <ILight.h>

namespace
  {
  class PyILight : public ILight
    {
    using ILight::ILight;
    };
  }

static void AddILight(py::module& io_module)
  {
  py::class_<ILight, PyILight>(io_module, "ILight");
  }