#pragma once
#include <ParticleSystem.h>

class SPHSystem : public ParticleSystem
  {
  public:
    SPHSystem(std::size_t i_num_particles);

    VectorDataIteratorC GetPositions() const;
    VectorDataIterator GetPositions();

    VectorDataIteratorC GetVelocities() const;
    VectorDataIterator GetVelocities();

    VectorDataIteratorC GetForces() const;
    VectorDataIterator GetForces();

    ScalarDataIteratorC GetDensities() const;
    ScalarDataIterator GetDensities();

    ScalarDataIteratorC GetPressures() const;
    ScalarDataIterator GetPressures();

    double GetRadius() const;
    void SetRadius(double i_radius);

    double GetMass() const;
    void SetMass(double i_mass);

  private:
    std::size_t m_positions_id;
    std::size_t m_velocities_id;
    std::size_t m_forces_id;

    std::size_t m_densities_id;
    std::size_t m_pressures_id;

    double m_radius;
    double m_mass;
  };

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetPositions() const
  {
  return _GetVectorDataAt(m_positions_id);
  }

inline ParticleSystem::VectorDataIterator  SPHSystem::GetPositions()
  {
  return _GetVectorDataAt(m_positions_id);
  }

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetVelocities() const
  {
  return _GetVectorDataAt(m_velocities_id);
  }

inline ParticleSystem::VectorDataIterator  SPHSystem::GetVelocities()
  {
  return _GetVectorDataAt(m_velocities_id);
  }

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetForces() const
  {
  return _GetVectorDataAt(m_forces_id);
  }

inline ParticleSystem::VectorDataIterator  SPHSystem::GetForces()
  {
  return _GetVectorDataAt(m_forces_id);
  }

inline ParticleSystem::ScalarDataIteratorC SPHSystem::GetDensities() const
  {
  return _GetScalarDataAt(m_densities_id);
  }

inline ParticleSystem::ScalarDataIterator  SPHSystem::GetDensities()
  {
  return _GetScalarDataAt(m_densities_id);
  }

inline ParticleSystem::ScalarDataIteratorC SPHSystem::GetPressures() const
  {
  return _GetScalarDataAt(m_pressures_id);
  }

inline ParticleSystem::ScalarDataIterator  SPHSystem::GetPressures()
  {
  return _GetScalarDataAt(m_pressures_id);
  }

inline double SPHSystem::GetMass() const
  {
  return m_mass;
  }

inline void SPHSystem::SetMass(double i_mass)
  {
  m_mass = i_mass;
  }

inline double SPHSystem::GetRadius() const
  {
  return m_radius;
  }

inline void SPHSystem::SetRadius(double i_radius)
  {
  m_radius = i_radius;
  }