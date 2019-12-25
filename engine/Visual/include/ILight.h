#pragma once
#include <string>

#include <Vector.h>

class ILight
  {
  public:
    virtual void SetState(bool i_state) = 0;
    virtual bool GetState() const = 0;
    virtual std::string Serialize() const = 0;
    virtual Vector3d GetDirection(const Vector3d& i_point) const = 0;
    virtual ~ILight() = default;
  };