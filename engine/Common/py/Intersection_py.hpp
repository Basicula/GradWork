#include <Intersection.h>

namespace
  {
  static void AddIntersectionClass(py::module& io_module)
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
                std::shared_ptr<IMaterial> ip_material)
                {
                io_intersection.m_material = ip_material;
                });
    }
  static void AddIntersectionUtils(py::module& io_module)
    {
    auto intersection_utils = io_module.def_submodule("Utils");
    intersection_utils.def("rayIntersectBox", RayIntersectBox);
    intersection_utils.def("rayBoxIntersection", RayBoxIntersection);
    }
  }

static void AddIntersectionSubmodule(py::module& io_module)
  {
  auto intersection_m = io_module.def_submodule("Intersection");
  AddIntersectionClass(intersection_m);
  AddIntersectionUtils(intersection_m);
  }