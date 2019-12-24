#pragma once

#include <Vector.h>
#include <IObject.h>

class Sphere : public IObject
  {
  public:
    Sphere(const Vector3d& i_center, double i_radius, const ColorMaterial& i_material = ColorMaterial());

    virtual bool IntersectWithRay(Intersection& o_intersection, const Ray& i_ray) const override;
    virtual std::string Serialize() const override;

    Vector3d GetCenter() const;
    void SetCenter(const Vector3d& i_center);

    double GetRadius() const;
    void SetRadius(double i_radius);

    ColorMaterial GetMaterial() const;
    void SetMaterial(const ColorMaterial& i_material);

  private:
    Vector3d m_center;
    double m_radius;
    ColorMaterial m_material;
  };

inline Vector3d Sphere::GetCenter() const 
  { 
  return m_center; 
  };

inline void Sphere::SetCenter(const Vector3d& i_center)
  {
  m_center = i_center;
  };

inline double Sphere::GetRadius() const 
  { 
  return m_radius; 
  };

inline void Sphere::SetRadius(double i_radius)
  {
  m_radius = i_radius;
  };

inline ColorMaterial Sphere::GetMaterial() const
  {
  return m_material;
  }

inline void Sphere::SetMaterial(const ColorMaterial& i_material)
  {
  m_material = i_material;
  }

inline std::string Sphere::Serialize() const
  {
  std::string res = "{ \"Sphere\" : { ";
  res += "\"Center\" : " + m_center.Serialize() + ", ";
  res += "\"Material\" : " + m_material.Serialize() + ", ";
  res += "\"Radius\" : " + std::to_string(m_radius);
  res += "} }";
  return res;
  }