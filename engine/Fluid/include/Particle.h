#pragma once

#include <Vector.h>

class Particle
  {
  public:
    Particle(const Vector3d& i_position);
    Particle(
      const Vector3d& i_position,
      const Vector3d& i_velocity);

    double GetDensity() const;
    void SetDensity(double i_density);

    Vector3d GetPosition() const;
    void SetPosition(const Vector3d& i_position);

    double GetPressure() const;
    void SetPressure(double i_pressure);

    Vector3d GetVelocity() const;
    void SetVelocity(const Vector3d& i_velocity);

    Vector3d GetAcceleration() const;
    void SetAcceleration(const Vector3d& i_acceleration);

  private:
    Vector3d m_position;
    Vector3d m_velocity;
    Vector3d m_force;
    Vector3d m_acceleration;

    double m_density;
    double m_pressure;
  };

inline double Particle::GetDensity() const
  {
  return m_density;
  }

inline void Particle::SetDensity(double i_density)
  {
  m_density = i_density;
  }

inline Vector3d Particle::GetPosition() const
  {
  return m_position;
  }

inline void Particle::SetPosition(const Vector3d& i_position)
  {
  m_position = i_position;
  }

inline double Particle::GetPressure() const
  {
  return m_pressure;
  }

inline void Particle::SetPressure(double i_pressure)
  {
  m_pressure = i_pressure;
  }

inline Vector3d Particle::GetVelocity() const
  {
  return m_velocity;
  }

inline void Particle::SetVelocity(const Vector3d& i_velocity)
  {
  m_velocity = i_velocity;
  }

inline Vector3d Particle::GetAcceleration() const
  {
  return m_acceleration;
  }

inline void Particle::SetAcceleration(const Vector3d& i_acceleration)
  {
  m_acceleration = i_acceleration;
  }