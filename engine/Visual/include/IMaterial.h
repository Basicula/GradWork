#pragma once
#include <string>
#include <vector>
#include <memory>

#include <Color.h>
#include <ILight.h>

class IMaterial
  {
  public:
    virtual std::string Serialize() const = 0;
    virtual Color GetPrimitiveColor() const = 0;
    virtual Color GetLightInfluence(
      const Vector3d& i_point,
      const Vector3d& i_normal, 
      std::shared_ptr<ILight> i_light) const = 0;
    virtual Color GetMultiLightInfluence(
      const Vector3d& i_point,
      const Vector3d& i_normal, 
      const std::vector<std::shared_ptr<ILight>>& i_lights) const = 0;
    virtual ~IMaterial() = default;
  };