#include <SPHSystem.h>

SPHSystem::SPHSystem(std::size_t i_num_particles)
  : ParticleSystem(i_num_particles)
  {
  m_positions_id = AddVectorData();
  m_velocities_id = AddVectorData();
  m_forces_id = AddVectorData();

  m_densities_id = AddScalarData();
  m_pressures_id = AddScalarData();
  }