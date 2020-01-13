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