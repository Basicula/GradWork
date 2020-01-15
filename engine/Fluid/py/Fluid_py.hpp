#include <Fluid.h>

namespace
  {
  class PyFluid : public Fluid
    {
    using Fluid::Fluid;
    bool IntersectWithRay(IntersectionRecord& io_intersection, const Ray& i_ray) const override
      {
      PYBIND11_OVERLOAD(
        bool,
        Fluid,
        IntersectWithRay,
        io_intersection,
        i_ray);
      }
    std::string Serialize() const override
      {
      PYBIND11_OVERLOAD(
        std::string,
        Fluid,
        Serialize,);
      }
    BoundingBox GetBoundingBox() const override
      {
      PYBIND11_OVERLOAD(
        BoundingBox,
        Fluid,
        GetBoundingBox, );
      }
    void ApplyPhysics() override
      {
      PYBIND11_OVERLOAD(
        void,
        Fluid,
        ApplyPhysics,);
      }
    };
  }

static void AddFluid(py::module& io_module)
  {
  py::class_<Fluid, std::shared_ptr<Fluid>, IObject, PyFluid>(io_module, "Fluid")
    .def(py::init<const BoundingBox&>())
    .def("fromDict", [](py::dict i_dict)
      {
      auto common_m = py::module::import("engine.Common");
      auto inner = i_dict["Fluid"];
      auto box = common_m.attr("BoundingBox").attr("fromDict")(inner["Box"]).cast<BoundingBox>();
      return Fluid(box);
      });
  }