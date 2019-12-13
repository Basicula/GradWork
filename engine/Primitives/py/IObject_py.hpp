#include <IObject.h>

namespace
  {
  class PyIObject : public IObject
    {
    using IObject::IObject;
    bool IntersectWithRay(Intersection& io_intersection, const Ray& i_ray) const override
      {
      PYBIND11_OVERLOAD_PURE(
        bool,
        IObject,
        IntersectWithRay,
        io_intersection,
        i_ray);
      };
    };
  }

static void AddIObject(py::module& io_module)
  {
  py::class_<IObject, PyIObject>(io_module, "IObject")
    .def("hitRay", &IObject::IntersectWithRay);
  }