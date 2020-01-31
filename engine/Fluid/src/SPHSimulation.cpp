#include <DefinesAndConstants.h>
#include <SPHSimulation.h>
#include <SPHSpikyKernel.h>
#include <ParallelUtils.h>

namespace
  {
  double ComputePressureFromEOS(
    double i_density,
    double i_system_density,
    double i_eos_scale,
    double i_eos_exponent,
    double i_negative_pressure_scale)
    {
    // See Murnaghan-Tait equation of state from
    // https://en.wikipedia.org/wiki/Tait_equation
    double pressure = i_eos_scale / i_eos_exponent
      * (std::pow((i_density / i_system_density), i_eos_exponent) - 1.0);

    // Negative pressure scaling
    if (pressure < 0)
      pressure *= i_negative_pressure_scale;

    return pressure;
    }
  }

SPHSimulation::SPHSimulation(std::size_t i_num_particles)
  : Simulation()
  , m_particle_system(i_num_particles)
  , m_new_positions(i_num_particles)
  , m_new_velocities(i_num_particles)
  , m_eos_exponent(7.15)
  , m_negative_pressure_scale(0.5)
  {}

void SPHSimulation::_PreProcessing()
  {
  m_particle_system.BuildNeighborSearcher();
  m_particle_system.BuildNeighborsList();
  m_particle_system.UpdateDensities();
  }

void SPHSimulation::_Update()
  {
  _AccumulateExternalForces();
  _AccumulatePressureForeces();

  _TimeIntegration();
  }

void SPHSimulation::_PostProcessing()
  {
  _UpdatePositionsAndVelocities();
  }

void SPHSimulation::_AccumulateExternalForces()
  {
  size_t num_of_particles = m_particle_system.GetNumOfParticles();
  auto forces = m_particle_system.GetForces();
  const double mass = m_particle_system.GetMass();

  Parallel::ParallelFor(
    static_cast<std::size_t>(0),
    num_of_particles,
    [&](std::size_t i_index)
    {
    // Gravity
    Vector3d force = Vector3d(0, -GRAVITY_CONSTANT, 0) * mass;

    // Wind forces
    forces[i_index] += force;
    });
  }

void SPHSimulation::_ComputePressure()
  {
  const auto num_of_particles = m_particle_system.GetNumOfParticles();
  auto densities = m_particle_system.GetDensities();
  auto pressures = m_particle_system.GetPressures();

  // See Murnaghan-Tait equation of state from
  // https://en.wikipedia.org/wiki/Tait_equation
  const double system_density = m_particle_system.GetSystemDensity();
  const double sqr_speed_of_sound = WATER_SPEED_OF_SOUND * WATER_SPEED_OF_SOUND;
  const double eos_scale = system_density * sqr_speed_of_sound;

  Parallel::ParallelFor(
    static_cast<std::size_t>(0),
    num_of_particles,
    [&](size_t i)
    {
    pressures[i] = ComputePressureFromEOS(
      densities[i],
      system_density,
      eos_scale,
      m_eos_exponent,
      m_negative_pressure_scale);
    });
  }

void SPHSimulation::_AccumulatePressureForeces()
  {
  _ComputePressure();
  size_t num_of_particles = m_particle_system.GetNumOfParticles();
  auto positions = m_particle_system.GetPositions();
  auto densities = m_particle_system.GetDensities();
  auto pressures = m_particle_system.GetPressures();
  auto forces = m_particle_system.GetForces();

  const double mass = m_particle_system.GetMass();
  const double square_mass = mass * mass;
  const auto& neigbors_list = m_particle_system.GetNeighborsList();
  const SPHSpikyKernel kernel(m_particle_system.GetRadius());

  Parallel::ParallelFor(
    static_cast<std::size_t>(0),
    num_of_particles,
    [&](std::size_t i)
    {
    const auto& neighbors = neigbors_list[i];
    for (auto j : neighbors)
      {
      double dist = positions[i].Distance(positions[j]);

      if (dist > 0.0)
        {
        Vector3d dir = (positions[j] - positions[i]) / dist;
        forces[i] -= kernel.Gradient(dist, dir) * square_mass
          * (pressures[i] / (densities[i] * densities[i])
          + pressures[j] / (densities[j] * densities[j]));
        }
      }
    });
  }

void SPHSimulation::_UpdatePositionsAndVelocities()
  {
  size_t num_of_particles = m_particle_system.GetNumOfParticles();
  auto positions = m_particle_system.GetPositions();
  auto velocities = m_particle_system.GetVelocities();
  Parallel::ParallelFor(
    static_cast<std::size_t>(0),
    num_of_particles,
    [&](size_t i)
    {
    positions[i] = m_new_positions[i];
    velocities[i] = m_new_velocities[i];
    });
  }

void SPHSimulation::_TimeIntegration()
  {
  size_t num_of_particles = m_particle_system.GetNumOfParticles();
  auto positions = m_particle_system.GetPositions();
  auto velocities = m_particle_system.GetVelocities();
  auto forces = m_particle_system.GetForces();
  Parallel::ParallelFor(
    static_cast<std::size_t>(0),
    num_of_particles,
    [&](std::size_t i)
    {
    m_new_velocities[i] = velocities[i] + 
      forces[i] * GetTimeStep() / m_particle_system.GetMass();

    m_new_positions[i] = positions[i] + m_new_velocities[i] * GetTimeStep();
    });
  }
