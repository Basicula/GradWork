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
  py::class_<Sphere, IObject, PySphere>(io_module, "Sphere")
    .def(py::init<Vector3d, double, ColorMaterial>(),
      py::arg("center"),
      py::arg("radius"),
      py::arg("material") = ColorMaterial())
    .def_property("center",
      &Sphere::GetCenter,
      &Sphere::SetCenter)
    .def_property("radius",
      &Sphere::GetRadius,
      &Sphere::SetRadius)
    .def_property("material",
      &Sphere::GetMaterial,
      &Sphere::SetMaterial);
  }