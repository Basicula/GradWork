#pragma once
#include <vector>

#include <IRenderable.h>
#include <BoundingBox.h>
#include <StandartParticle.h>
#include <SPHSimulation.h>

class Ray;
struct Intersection;

class Fluid : public IRenderable
  {
  public:
    Fluid(const BoundingBox& i_box);

    virtual bool IntersectWithRay(
      IntersectionRecord& o_intersection,
      const Ray& i_ray) const override;
    virtual std::string Serialize() const override;
    BoundingBox GetBoundingBox() const;
    //TODO
    //virtual void ApplyPhysics() override;

    double GetTimeStep();

  private:
    void _InitParticles();

  private:
    BoundingBox m_bbox;
    SPHSimulation m_simulation;
  };

inline std::string Fluid::Serialize() const
  {
  std::string res = "{ \"Fluid\" : { ";
  res += "\"Box\" : " + m_bbox.Serialize();
  res += "} }";
  return res;
  }

inline BoundingBox Fluid::GetBoundingBox() const
  {
  return m_bbox;
  }

inline double Fluid::GetTimeStep()
  {
  return m_simulation.GetTimeStep();
  }

  //TODO
//inline void Fluid::ApplyPhysics()
//  {
//  m_simulation.Update();
//  }