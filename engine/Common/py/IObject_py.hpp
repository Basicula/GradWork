#include <IObject.h>

namespace
  {
  class PyIObject : public IObject
    {
    using IObject::IObject;
    bool IntersectWithRay(IntersectionRecord& io_intersection, const Ray& i_ray) const override
      {
      PYBIND11_OVERLOAD_PURE(
        bool,
        IObject,
        IntersectWithRay,
        io_intersection,
        i_ray);
      }
    std::string Serialize() const override
      {
      PYBIND11_OVERLOAD_PURE(
        std::string,
        IObject,
        Serialize,
        );
      }
    BoundingBox GetBoundingBox() const override
      {
      PYBIND11_OVERLOAD_PURE(
        BoundingBox,
        IObject,
        GetBoundingBox,);
      }
    void ApplyPhysics() override
      {
      PYBIND11_OVERLOAD_PURE(
        void,
        IObject,
        ApplyPhysics,);
      }
    };
  }

static void AddIObject(py::module& io_module)
  {
  py::class_<IObject, std::shared_ptr<IObject>, PyIObject>(io_module, "IObject")
    .def("hitRay", &IObject::IntersectWithRay)
    .def("applyPhysics", &IObject::ApplyPhysics)
    .def_property_readonly("boundingBox", &IObject::GetBoundingBox)
    .def("__repr__", &IObject::Serialize)
    .def("fromDict", [](py::dict i_dict)
      {
      auto primitives_m = py::module::import("engine.Primitives");
      if (i_dict.contains("Sphere"))
        return primitives_m.attr("Sphere").attr("fromDict")(i_dict).cast<std::shared_ptr<IObject>>();
      return std::shared_ptr<IObject>();
      });
  }