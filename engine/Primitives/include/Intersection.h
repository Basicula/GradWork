#pragma once

#include <Vector.h>
#include <ColorMaterial.h>

struct Intersection
  {
  double m_distance;
  Vector3d m_intersection;
  Vector3d m_normal;
  ColorMaterial m_material;
  };