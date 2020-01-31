#pragma once
#include <FluidConstants.h>
#include <ParticleSystem.h>
#include <PointNeighborSearcher.h>

class SPHSystem : public ParticleSystem
  {
  public:
    SPHSystem(
      std::size_t i_num_particles = 1024,
      double i_system_density = WATER_DENSITY,
      double i_radius = SMOOTHING_RADIUS,
      double i_mass = PARTICLE_MASS);

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

    double GetSystemDensity() const;
    void SetSystemDensity(double i_system_density);

    double GetRadius() const;
    void SetRadius(double i_radius);

    double GetMass() const;
    void SetMass(double i_mass);

    void BuildNeighborSearcher();
    void BuildNeighborsList();
    void UpdateDensities();

    std::vector<std::vector<std::size_t>> GetNeighborsList() const;

  private:
    double _SumOfKernelsNearby(const Vector3d& i_origin) const;

  private:
    std::size_t m_positions_id;
    std::size_t m_velocities_id;
    std::size_t m_forces_id;

    std::size_t m_densities_id;
    std::size_t m_pressures_id;

    double m_system_density;

    double m_radius;
    double m_mass;

    PointNeighborSearcherPtr mp_neighbor_searcher;
    std::vector<std::vector<std::size_t>> m_neighbors_list;
  };

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetPositions() const
  {
  return _GetVectorDataAt(m_positions_id);
  }

inline ParticleSystem::VectorDataIterator SPHSystem::GetPositions()
  {
  return _GetVectorDataAt(m_positions_id);
  }

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetVelocities() const
  {
  return _GetVectorDataAt(m_velocities_id);
  }

inline ParticleSystem::VectorDataIterator SPHSystem::GetVelocities()
  {
  return _GetVectorDataAt(m_velocities_id);
  }

inline ParticleSystem::VectorDataIteratorC SPHSystem::GetForces() const
  {
  return _GetVectorDataAt(m_forces_id);
  }

inline ParticleSystem::VectorDataIterator SPHSystem::GetForces()
  {
  return _GetVectorDataAt(m_forces_id);
  }

inline ParticleSystem::ScalarDataIteratorC SPHSystem::GetDensities() const
  {
  return _GetScalarDataAt(m_densities_id);
  }

inline ParticleSystem::ScalarDataIterator SPHSystem::GetDensities()
  {
  return _GetScalarDataAt(m_densities_id);
  }

inline ParticleSystem::ScalarDataIteratorC SPHSystem::GetPressures() const
  {
  return _GetScalarDataAt(m_pressures_id);
  }

inline ParticleSystem::ScalarDataIterator SPHSystem::GetPressures()
  {
  return _GetScalarDataAt(m_pressures_id);
  }

inline double SPHSystem::GetSystemDensity() const
  {
  return m_system_density;
  }

inline void SPHSystem::SetSystemDensity(double i_system_density)
  {
  m_system_density = i_system_density;
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

inline std::vector<std::vector<std::size_t>> SPHSystem::GetNeighborsList() const
  {
  return m_neighbors_list;
  }