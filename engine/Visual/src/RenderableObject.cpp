#include <RenderableObject.h>

RenderableObject::RenderableObject(
  ISurfaceSPtr i_surface, 
  IMaterialSPtr i_material)
  : mp_surface(i_surface)
  , mp_material(i_material)
  {}

bool RenderableObject::IntersectWithRay(
  IntersectionRecord& o_intersection, 
  const Ray& i_ray) const
  {
  RaySurfaceIntersection intersection;
  if (mp_surface->IntersectWithRay(intersection, i_ray))
    {
    o_intersection = intersection;
    o_intersection.m_material = mp_material;
    return true;
    }

  return false;
  }
