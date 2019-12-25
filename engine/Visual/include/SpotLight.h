#pragma once

#include <ILight.h>
#include <Vector.h>
#include <Color.h>

class SpotLight : public ILight
  {
  public:
    SpotLight(
      const Vector3d& i_location, 
      const Color& i_color = Color(255, 255, 255), 
      double i_intensity = 1.0,
      bool i_state = true);

    Vector3d GetLocation() const;
    void SetLocation(const Vector3d& i_location);
    Color GetColor() const;
    void SetColor(const Color& i_color);
    double GetIntensity() const;
    void SetIntensity(double i_intensity);

    virtual void SetState(bool i_state) override;
    virtual bool GetState() const override;
    virtual std::string Serialize() const override;
    virtual Vector3d GetDirection(const Vector3d& i_point) const override;
    
    double GetIntensityAtPoint(const Vector3d& i_point) const;

  private:
    Vector3d m_location;
    Color m_color;
    double m_intensity;
    // true - on, false - off
    bool m_state;
  };
  
inline Vector3d SpotLight::GetLocation() const 
  { 
  return m_location; 
  };
  
inline void SpotLight::SetLocation(const Vector3d& i_location)
  { 
  m_location = i_location;
  };

inline Color SpotLight::GetColor() const 
  { 
  return m_color; 
  };
  
inline void SpotLight::SetColor(const Color& i_color)
  { 
  m_color = i_color; 
  };

inline double SpotLight::GetIntensity() const 
  { 
  return m_intensity;
  };
  
inline void SpotLight::SetIntensity(double i_intensity)
  { 
  m_intensity = i_intensity; 
  };

inline void SpotLight::SetState(bool i_state)
  {
  m_state = i_state;
  }

inline bool SpotLight::GetState() const
  {
  return m_state;
  }

inline std::string SpotLight::Serialize() const
  {
  std::string res = "{ \"SpotLight\" : { ";
  res += " \"Location\" : " + m_location.Serialize() + ", ";
  res += " \"Color\" : " + m_color.Serialize() + ", ";
  res += " \"Intensity\" : " + std::to_string(m_intensity) + ", ";
  res += " \"State\" : " + std::to_string(m_state);
  res += " } }";
  return res;
  }

inline Vector3d SpotLight::GetDirection(const Vector3d& i_point) const
  {
  return (i_point - m_location).Normalized();
  }