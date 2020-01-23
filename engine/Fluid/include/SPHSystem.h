#pragma once
#include <ParticleSystem.h>

class SPHSystem : public ParticleSystem
  {
  public:
    SPHSystem(std::size_t i_num_particles);

  private:
    std::size_t m_positions_id;
    std::size_t m_velocities_id;
    std::size_t m_forces_id;

    std::size_t m_densities_id;
    std::size_t m_pressures_id;
  };