#include <ILight.h>

namespace
  {
  class PyILight : public ILight
    {
    using ILight::ILight;
    void SetState(bool i_state) override
      {
      PYBIND11_OVERLOAD_PURE(
        void,
        ILight,
        SetState,
        i_state);
      }
    bool GetState() const override
      {
      PYBIND11_OVERLOAD_PURE(
        bool,
        ILight,
        GetState,
        );
      }
    };
  }

static void AddILight(py::module& io_module)
  {
  py::class_<ILight, std::shared_ptr<ILight>, PyILight>(io_module, "ILight")
    .def_property("state",
      &ILight::GetState,
      &ILight::SetState);
  }