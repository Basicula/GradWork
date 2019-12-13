#pragma once
#include <Ray.h>
#include <Intersection.h>

class IObject
  {
  public:
    virtual bool IntersectWithRay(Intersection& o_intersection, const Ray& i_ray) const = 0;

    virtual ~IObject() = default;
  };