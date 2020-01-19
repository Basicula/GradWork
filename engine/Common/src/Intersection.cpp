#include <Intersection.h>
#include <BoundingBox.h>
#include <Ray.h>
#include <DefinesAndConstants.h>

IntersectionRecord::IntersectionRecord()
  : m_distance(MAX_DOUBLE)
  , m_intersection(Vector3d(0))
  , m_normal(Vector3d(0))
  , m_material(nullptr)
  {}

RayBoxIntersectionRecord::RayBoxIntersectionRecord()
  : m_intersected(false)
  , m_tmax(-MAX_DOUBLE)
  , m_tmin(MAX_DOUBLE)
  {}

void RayBoxIntersection(
  const Ray & i_ray,
  const BoundingBox & i_box, 
  RayBoxIntersectionRecord& o_intersection)
  {
  const auto& min_corner = i_box.GetMin();
  const auto& max_corner = i_box.GetMax();
  const auto& origin = i_ray.GetOrigin();
  const auto& ray_direction = i_ray.GetDirection();

  o_intersection.m_tmin = 0;
  o_intersection.m_tmax = MAX_DOUBLE;
  for (auto i = 0; i < 3; ++i)
    {
    double ttmin = (min_corner[i] - origin[i]) / ray_direction[i];
    double ttmax = (max_corner[i] - origin[i]) / ray_direction[i];

    if (ttmin > ttmax)
      std::swap(ttmin, ttmax);

    if (ttmin > o_intersection.m_tmin)
      o_intersection.m_tmin = ttmin;
    if (ttmax < o_intersection.m_tmax)
      o_intersection.m_tmax = ttmax;

    if (o_intersection.m_tmin > o_intersection.m_tmax)
      {
      o_intersection.m_intersected = false;
      return;
      }
    }

  o_intersection.m_intersected = true;
  }

bool RayIntersectBox(
  const Ray& i_ray,
  const BoundingBox& i_box)
  {
  RayBoxIntersectionRecord temp;
  RayBoxIntersection(i_ray, i_box, temp);
  return temp.m_intersected;
  }