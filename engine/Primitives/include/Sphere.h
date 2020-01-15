#pragma once
#include <memory>

#include <Vector.h>
#include <IObject.h>
#include <IMaterial.h>
#include <Ray.h>
#include <Intersection.h>
#include <BoundingBox.h>

class Sphere : public IObject
  {
  public:
    Sphere(const Vector3d& i_center, double i_radius, std::shared_ptr<IMaterial> ip_material = nullptr);

    virtual bool IntersectWithRay(IntersectionRecord& o_intersection, const Ray& i_ray) const override;
    virtual std::string Serialize() const override;
    virtual BoundingBox GetBoundingBox() const override;
    virtual void ApplyPhysics() override;

    Vector3d GetCenter() const;
    void SetCenter(const Vector3d& i_center);

    double GetRadius() const;
    void SetRadius(double i_radius);

    std::shared_ptr<IMaterial> GetMaterial() const;
    void SetMaterial(std::shared_ptr<IMaterial> i_material);

  private:
    Vector3d m_center;
    double m_radius;
    std::shared_ptr<IMaterial> m_material;
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

inline std::shared_ptr<IMaterial> Sphere::GetMaterial() const
  {
  return m_material;
  }

inline void Sphere::SetMaterial(std::shared_ptr<IMaterial> i_material)
  {
  m_material = i_material;
  }

inline std::string Sphere::Serialize() const
  {
  std::string res = "{ \"Sphere\" : { ";
  res += "\"Center\" : " + m_center.Serialize() + ", ";
  res += "\"Material\" : " + ( m_material ?  m_material->Serialize() : "null" ) + ", ";
  res += "\"Radius\" : " + std::to_string(m_radius);
  res += "} }";
  return res;
  }

inline BoundingBox Sphere::GetBoundingBox() const
  {
  return BoundingBox(m_center - m_radius, m_center + m_radius);
  }

inline void Sphere::ApplyPhysics()
  {
  
  }