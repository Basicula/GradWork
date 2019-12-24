#pragma once
#include <string>

class ILight
  {
  public:
    virtual void SetState(bool i_state) = 0;
    virtual bool GetState() const = 0;
    virtual std::string Serialize() const = 0;
    virtual ~ILight() = default;
  };