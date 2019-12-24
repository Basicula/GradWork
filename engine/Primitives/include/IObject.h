#pragma once
#include <string>

#include <Ray.h>
#include <Intersection.h>

class IObject
  {
  public:
    virtual bool IntersectWithRay(Intersection& o_intersection, const Ray& i_ray) const = 0;
    virtual std::string Serialize() const = 0;

    virtual ~IObject() = default;
  };