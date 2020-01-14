#pragma once
#include <memory>

#include <Vector.h>
class IMaterial;

struct Intersection
  {
  double m_distance;
  Vector3d m_intersection;
  Vector3d m_normal;
  std::shared_ptr<IMaterial> m_material;

  Intersection();
  };

class BoundingBox;
class Ray;

// if result is true 
// o_tmin and o_tmax contain near and far distance to box
// if result is false
// o_tmin and o_tmax contain garbage
bool RayBoxIntersection(
  const Ray& i_ray,
  const BoundingBox& i_box, 
  double& o_tmin,
  double& o_tmax);

bool RayIntersectBox(
  const Ray& i_ray,
  const BoundingBox& i_box);