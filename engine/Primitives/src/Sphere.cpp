#include <Sphere.h>
#include <DefinesAndConstants.h>

Sphere::Sphere(const Vector3d& i_center, double i_radius, std::shared_ptr<IMaterial> ip_material)
  : m_center(i_center)
  , m_radius(i_radius)
  , m_material(ip_material)
  {}

bool Sphere::IntersectWithRay(IntersectionRecord& o_intersection, const Ray& i_ray) const
  {
  const auto& ray_origin = i_ray.GetOrigin();
  const auto& ray_direction = i_ray.GetDirection();
  const auto& start_to_center = m_center - ray_origin;

  const double to_sphere = start_to_center.Dot(ray_direction);

  if (to_sphere - m_radius > o_intersection.m_distance)
    return false;

  const auto& point_near_sphere = ray_origin + ray_direction * to_sphere;

  const double sqr_radius = m_radius * m_radius;
  const double sphere_center_to_point = m_center.SquareDistance(point_near_sphere);
  if (sphere_center_to_point > sqr_radius)
    return false;

  const double distance_to_intersection = to_sphere - sqrt(sqr_radius - sphere_center_to_point);
  if (distance_to_intersection <= Epsilon3D)
    return false;

  if (o_intersection.m_distance < distance_to_intersection && o_intersection.m_distance > 0)
    return false;

  o_intersection.m_distance = distance_to_intersection;
  o_intersection.m_intersection = ray_origin + ray_direction * distance_to_intersection;
  o_intersection.m_material = m_material;
  o_intersection.m_normal = (o_intersection.m_intersection - m_center).Normalized();
  return true;
  }