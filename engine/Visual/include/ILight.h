#pragma once

class ILight
  {
  public:
    virtual void SetState(bool i_state) = 0;
    virtual bool GetState() const = 0;
    virtual ~ILight() = default;
  };