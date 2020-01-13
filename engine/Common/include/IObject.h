#pragma once
#include <string>

struct Intersection;
class Ray;
class BoundingBox;

class IObject
  {
  public:
    virtual void ApplyPhysics() = 0;
    virtual bool IntersectWithRay(Intersection& o_intersection, const Ray& i_ray) const = 0;
    virtual std::string Serialize() const = 0;

    virtual BoundingBox GetBoundingBox() const = 0;

    virtual ~IObject() = default;
  };