#pragma once
#include <string>

class IMaterial
  {
  public:
    virtual std::string Serialize() const = 0;
    virtual ~IMaterial() = default;
  };