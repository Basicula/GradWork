#include <Sphere.h>

namespace
  {
  class PySphere : public Sphere
    {
    using Sphere::Sphere;
    bool IntersectWithRay(Intersection& io_intersection, const Ray& i_ray) const override
      {
      PYBIND11_OVERLOAD(
        bool,
        Sphere,
        IntersectWithRay,
        io_intersection,
        i_ray);
      };
    };
  }

static void AddSphere(py::module& io_module)
  {
  py::class_<Sphere, std::shared_ptr<Sphere>, IObject, PySphere>(io_module, "Sphere")
    .def(py::init<Vector3d, double, std::shared_ptr<IMaterial>>(),
      py::arg("center"),
      py::arg("radius"),
      py::arg("material") = nullptr)
    .def_property("center",
      &Sphere::GetCenter,
      &Sphere::SetCenter)
    .def_property("radius",
      &Sphere::GetRadius,
      &Sphere::SetRadius)
    .def_property("material",
      &Sphere::GetMaterial,
      &Sphere::SetMaterial)
    .def("fromDict", [](py::dict i_dict)
      {
      auto vec_m = py::module::import("engine.Math.Vector");
      auto material_m = py::module::import("engine.Visual.Material");
      auto inner = i_dict["Sphere"];
      Vector3d center = vec_m.attr("Vector3d").attr("fromDict")(inner["Center"]).cast<Vector3d>();
      auto material = std::shared_ptr<IMaterial>();
      if (!inner["Material"].is_none())
        material = material_m.attr("IMaterial").attr("fromDict")(inner["Material"]).cast<std::shared_ptr<IMaterial>>();
      double radius = inner["Radius"].cast<double>();
      return Sphere(center,radius,material);
      });
  }