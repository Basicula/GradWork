#include "Ray.h"

Ray::Ray(const Vector3d& i_origin, const Vector3d& i_dir)
  : m_origin(i_origin)
  , m_direction(i_dir.Normalized())
  {}