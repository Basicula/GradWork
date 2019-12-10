#pragma once

#include <Color.h>
#include <Vector.h>

class ColorMaterial
  {
  public:
    ColorMaterial() = delete;
    ColorMaterial(
      const Color& i_color,
      const Vector3d& i_ambient = Vector3d(1.0, 1.0, 1.0),
      const Vector3d& i_diffuse = Vector3d(1.0, 1.0, 1.0),
      const Vector3d& i_specular = Vector3d(1.0, 1.0, 1.0),
      double i_shinines = 1.0,
      double i_reflection = 0.0,
      double i_refraction = 0.0);

    Color GetResultColor(
      const Vector3d& i_normal, 
      const Vector3d& i_light, 
      const Vector3d& i_view) const;

    Color GetBaseColor() const;
    Color GetAmbientColor() const;
    Color GetDiffuseColor() const;
    Color GetSpecularColor() const;
    
    Vector3d GetAmbient() const;
    void SetAmbient(const Vector3d& i_ambient);
    
    Vector3d GetDiffuse() const;
    void SetDiffuse(const Vector3d& i_diffuse);
    
    Vector3d GetSpecular() const;
    void SetSpecular(const Vector3d& i_specular);
    
    double GetReflection() const;
    void SetReflection(double i_reflection);
    
    double GetRefraction() const;
    void SetRefraction(double i_refraction);

  private:
    Color m_color;
    double m_shinines;

    //x,y,z == r,g,b(coefs) in [0,1]
    Vector3d m_ambient;
    Vector3d m_diffuse;
    Vector3d m_specular;
    
    //[0,1]
    double m_reflection;

    double m_refraction;
  };

const ColorMaterial g_DefaultMaterial(Color(255,255,255));

inline Color ColorMaterial::GetBaseColor() const 
  { 
  return m_color; 
  };
  
inline Color ColorMaterial::GetAmbientColor() const 
  { 
  return m_color * m_ambient; 
  };
  
inline Vector3d ColorMaterial::GetAmbient() const 
  { 
  return m_ambient; 
  };
  
inline void ColorMaterial::SetAmbient(const Vector3d& i_ambient) 
  { 
  m_ambient = i_ambient; 
  };
  
inline Color ColorMaterial::GetDiffuseColor() const 
  { 
  return m_color * m_diffuse; 
  };
    
inline Vector3d ColorMaterial::GetDiffuse() const 
  { 
  return m_diffuse; 
  };
  
inline void ColorMaterial::SetDiffuse(const Vector3d& i_diffuse) 
  { 
  m_diffuse = i_diffuse; 
  };
  
inline Color ColorMaterial::GetSpecularColor() const 
  { 
  return m_color * m_specular; 
  };
  
inline Vector3d ColorMaterial::GetSpecular() const 
  { 
  return m_specular; 
  };
  
inline void ColorMaterial::SetSpecular(const Vector3d& i_specular) 
  { 
  m_specular = i_specular; 
  };
  
inline double ColorMaterial::GetReflection() const 
  { 
  return m_reflection; 
  };
  
inline void ColorMaterial::SetReflection(double i_reflection)
  { 
  m_reflection = i_reflection; 
  };

inline double ColorMaterial::GetRefraction() const 
  { 
  return m_refraction; 
  };
  
inline void ColorMaterial::SetRefraction(double i_refraction)
  { 
  m_refraction = i_refraction; 
  };