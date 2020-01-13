#include <Particle.h>

Particle::Particle(const Vector3d& i_position)
  : m_position(i_position)
  , m_velocity(0)
  , m_force(0)
  , m_acceleration(0)
  , m_density(0)
  , m_pressure(0)
  {}

Particle::Particle(
  const Vector3d& i_position,
  const Vector3d& i_velocity)
  : m_position(i_position)
  , m_velocity(i_velocity)
  , m_force(0)
  , m_acceleration(0)
  , m_density(0)
  , m_pressure(0)
  {}