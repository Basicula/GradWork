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
      double i_intensity = 1.0);

    Vector3d GetLocation() const;
    void SetLocation(const Vector3d& i_location);
    Color GetColor() const;
    void SetColor(const Color& i_color);
    double GetIntensity() const;
    void SetIntensity(double i_intensity);
    
    double GetIntensityAtPoint(const Vector3d& i_point) const;

  private:
    Vector3d m_location;
    Color m_color;
    double m_intensity;
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