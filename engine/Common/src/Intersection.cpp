#include <Intersection.h>
#include <BoundingBox.h>
#include <Ray.h>
#include <DefinesAndConstants.h>

Intersection::Intersection()
  : m_distance(-1)
  , m_intersection(Vector3d(0))
  , m_normal(Vector3d(0))
  , m_material(nullptr)
  {}

bool RayBoxIntersection(
  const Ray & i_ray,
  const BoundingBox & i_box, 
  double& o_tmin,
  double& o_tmax)
  {
  const auto& min_corner = i_box.GetMin();
  const auto& max_corner = i_box.GetMax();
  const auto& origin = i_ray.GetOrigin();
  const auto& inv_direction = i_ray.GetDirection().Inversed();

  o_tmin = 0;
  o_tmax = MAX_DOUBLE;
  for (auto i = 0; i < 3; ++i)
    {
    double ttmin = (min_corner[i] - origin[i]) * inv_direction[i];
    double ttmax = (max_corner[i] - origin[i]) * inv_direction[i];

    if (ttmin > ttmax)
      std::swap(ttmin, ttmax);

    if (ttmin > o_tmin)
      o_tmin = ttmin;
    if (ttmax < o_tmax)
      o_tmax = ttmax;

    if (o_tmin > o_tmax) 
      return false;
    }

  return true;
  }

bool RayIntersectBox(
  const Ray& i_ray,
  const BoundingBox& i_box)
  {
  double temp_min, temp_max;
  return RayBoxIntersection(
    i_ray,
    i_box,
    temp_min,
    temp_max);
  }