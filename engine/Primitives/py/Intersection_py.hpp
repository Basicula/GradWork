#include <Intersection.h>

static void AddIntersection(py::module& io_module)
  {
  py::class_<Intersection>(io_module, "Intersection")
    .def(py::init<>())
    .def_property("intersection",
      [](const Intersection& i_intersection)
      {
      return i_intersection.m_intersection;
      },
      [](Intersection& io_intersection,
        const Vector3d& i_intersection)
        {
        io_intersection.m_intersection = i_intersection;
        })
    .def_property("normal",
      [](const Intersection& i_intersection)
      {
      return i_intersection.m_normal;
      },
      [](Intersection& io_intersection,
        const Vector3d& i_normal)
        {
        io_intersection.m_normal = i_normal;
        })
    .def_property("distance",
      [](const Intersection& i_intersection)
      {
      return i_intersection.m_distance;
      },
      [](Intersection& io_intersection,
        double i_distance)
        {
        io_intersection.m_distance = i_distance;
        })
    .def_property("material",
      [](const Intersection& i_intersection)
      {
      return i_intersection.m_material;
      },
      [](Intersection& io_intersection,
        const ColorMaterial& i_material)
        {
        io_intersection.m_material = i_material;
        });
  }