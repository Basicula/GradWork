#pragma once
#include <memory>

#include <Vector.h>
class IMaterial;

struct IntersectionRecord
  {
  double m_distance;
  Vector3d m_intersection;
  Vector3d m_normal;
  std::shared_ptr<IMaterial> m_material;

  IntersectionRecord();

  // updates current if other is closer
  void Update(const IntersectionRecord& i_other);

  void Reset();
  };

struct RayBoxIntersectionRecord
  {
  bool m_intersected;
  double m_tmin;
  double m_tmax;

  RayBoxIntersectionRecord();

  void Reset();
  };

class BoundingBox;
class Ray;

// if result is true 
// o_tmin and o_tmax contain near and far distance to box
// if result is false
// o_tmin and o_tmax contain garbage
void RayBoxIntersection(
  const Ray& i_ray,
  const BoundingBox& i_box, 
  RayBoxIntersectionRecord& o_intersection);

bool RayIntersectBox(
  const Ray& i_ray,
  const BoundingBox& i_box);