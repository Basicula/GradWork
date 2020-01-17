#include <Fluid.h>
#include <DefinesAndConstants.h>
#include <FluidConstants.h>
#include <Sphere.h>
#include <ColorMaterial.h>

namespace
  {
  double Wpoly6(double i_squared_radius)
    {
    const double coefficient = 315.0 / (64.0 * PI * pow(SMOOTHING_RADIUS, 9));
    return coefficient * pow(SMOOTHING_RADIUS_SQR - i_squared_radius, 3);
    }

  Vector3d Wpoly6Gradient(const Vector3d& i_position_difference, double i_squared_radius)
    {
    const double coefficient = -945.0 / (32.0 * PI * pow(SMOOTHING_RADIUS, 9));
    return i_position_difference * coefficient * pow(SMOOTHING_RADIUS_SQR - i_squared_radius, 2);
    }

  double Wpoly6Laplacian(double i_squared_radius)
    {
    const double coefficient = -945.0 / (32.0 * PI * pow(SMOOTHING_RADIUS, 9));
    return coefficient * (SMOOTHING_RADIUS_SQR - i_squared_radius) * (3.0 * SMOOTHING_RADIUS_SQR - 7.0 * i_squared_radius);
    }

  Vector3d WspikyGradient(const Vector3d& i_position_difference, double i_squared_radius)
    {
    const double coefficient = -45.0 / (PI * pow(SMOOTHING_RADIUS, 6));
    const double radius = sqrt(i_squared_radius);
    return i_position_difference * coefficient * pow(SMOOTHING_RADIUS - radius, 2) / radius;
    }

  double WviscosityLaplacian(double i_squared_radius)
    {
    const double coefficient = 45.0 / (PI * pow(SMOOTHING_RADIUS, 6));
    const double radius = sqrt(i_squared_radius);
    return coefficient * (SMOOTHING_RADIUS - radius);
    }
  }

const double Fluid::m_dt = 0.1;

Fluid::Fluid(const BoundingBox& i_box)
  : m_bbox(i_box)
  , m_grid(10, 10, 10)
  {
  _InitParticles();
  }

void Fluid::_InitParticles()
  {
  for (int i = 0; i < 1024; ++i)
    m_particles.emplace_back(Vector3d(-2 + i * SMOOTHING_RADIUS / 2, 1, 0), Vector3d(0, 1, 0));
  _UpdateGrid();
  }

void Fluid::_Step()
  {
  _UpdateDensityAndPressure();
  _ComputeForcesForParticles();
  _UpdatePositionAndVelocity();
  _UpdateGrid();
  }

void Fluid::_BruteForceStep()
  {
  _BruteUpdateDensityAndPressure();
  _BruteComputeForcesForParticles();
  _UpdatePositionAndVelocity();
  }

void Fluid::_BruteUpdateDensityAndPressure()
  {
  for (int i = 0; i < m_particles.size(); ++i)
    {
    double density = 0;
    for (int j = 0; j < m_particles.size(); ++j)
      {
      auto sqr_particles_distance = m_particles[i].GetPosition().SquareDistance(m_particles[j].GetPosition());

      if (sqr_particles_distance < SMOOTHING_RADIUS_SQR)
        density += Wpoly6(sqr_particles_distance);
      }
    density *= PARTICLE_MASS;
    m_particles[i].SetDensity(density);
    m_particles[i].SetPressure(GAS_STIFFNESS * (density - REST_DENSITY));
    }
  }

void Fluid::_UpdateDensityAndPressure()
  {
  for (auto x = 0; x < m_grid.m_x; ++x)
    for (auto y = 0; y < m_grid.m_y; ++y)
      for (auto z = 0; z < m_grid.m_z; ++z)
        {
        const Cell& cell = m_grid(x, y, z);
        for (auto particle : cell)
          {
          double density = 0;
          auto neighbours = m_grid.GetNeigbourParticles(x, y, z);
          for (auto neighbour : neighbours)
            {
            auto sqr_particles_distance = particle->GetPosition().SquareDistance(neighbour->GetPosition());

            if (sqr_particles_distance < SMOOTHING_RADIUS_SQR)
              density += Wpoly6(sqr_particles_distance);
            }
          density *= PARTICLE_MASS;
          particle->SetDensity(density);
          particle->SetPressure(GAS_STIFFNESS * (density - REST_DENSITY));
          }
        }
  }

void Fluid::_BruteComputeForcesForParticles()
  {
  for (int i = 0; i < m_particles.size(); ++i)
    {
    // forces
    Vector3d f_pressure;
    Vector3d f_viscosity;
    for (int j = 0; j < m_particles.size(); ++j)
      {
      auto diff = m_particles[i].GetPosition() - m_particles[j].GetPosition();
      auto sqr_particles_distance = diff.SquareLength();

      if (sqr_particles_distance < SMOOTHING_RADIUS_SQR)
        {
        Vector3d poly6Gradient = Wpoly6Gradient(diff, sqr_particles_distance);

        const double sqr_particle_density = m_particles[i].GetDensity() * m_particles[i].GetDensity();
        const double sqr_neighbour_density = m_particles[j].GetDensity() * m_particles[j].GetDensity();

        f_pressure += poly6Gradient * (m_particles[i].GetPressure() / sqr_particle_density + m_particles[j].GetPressure() / sqr_neighbour_density);
        f_viscosity += (m_particles[j].GetVelocity() - m_particles[i].GetVelocity()) * WviscosityLaplacian(sqr_particles_distance);
        }
      }
    f_pressure *= -PARTICLE_MASS * m_particles[i].GetDensity();
    f_viscosity *= VISCOSITY * PARTICLE_MASS;

    const Vector3d f_gravity(0, GRAVITY_ACCELERATION * m_particles[i].GetDensity(), 0);

    Vector3d f_surface;
    m_particles[i].SetAcceleration((f_pressure + f_viscosity + f_surface + f_gravity) / m_particles[i].GetDensity());
    }
  }

void Fluid::_ComputeForcesForParticles()
  {
  for (auto x = 0; x < m_grid.m_x; ++x)
    for (auto y = 0; y < m_grid.m_y; ++y)
      for (auto z = 0; z < m_grid.m_z; ++z)
        {
        const Cell& cell = m_grid(x, y, z);
        for (auto particle : cell)
          {
          // forces
          Vector3d f_pressure;
          Vector3d f_viscosity;
          auto neighbours = m_grid.GetNeigbourParticles(x, y, z);
          for (auto neighbour : neighbours)
            {
            if (particle == neighbour)
              continue;
            auto diff = particle->GetPosition() - neighbour->GetPosition();
            auto sqr_particles_distance = diff.SquareLength();

            if (sqr_particles_distance < SMOOTHING_RADIUS_SQR)
              {
              Vector3d poly6Gradient = Wpoly6Gradient(diff, sqr_particles_distance);
              Vector3d spikyGradient = WspikyGradient(diff, sqr_particles_distance);

              const double sqr_particle_density = particle->GetDensity() * particle->GetDensity();
              const double sqr_neighbour_density = neighbour->GetDensity() * neighbour->GetDensity();

              f_pressure += spikyGradient * (particle->GetPressure() / sqr_particle_density + neighbour->GetPressure() / sqr_neighbour_density);
              f_viscosity += (neighbour->GetVelocity() - particle->GetVelocity()) * WviscosityLaplacian(sqr_particles_distance);
              }
            }
          f_pressure *= -PARTICLE_MASS * particle->GetDensity();
          f_viscosity *= VISCOSITY * PARTICLE_MASS;

          const Vector3d f_gravity(0, GRAVITY_ACCELERATION * particle->GetDensity(), 0);

          Vector3d f_surface;
          particle->SetAcceleration((f_pressure + f_viscosity + f_surface + f_gravity) / particle->GetDensity());
          }
        }
  }

void Fluid::_UpdatePositionAndVelocity()
  {
  for (auto& particle : m_particles)
    {
    const Vector3d newPosition = particle.GetPosition() + particle.GetVelocity() * m_dt + particle.GetAcceleration() * m_dt * m_dt;
    const Vector3d newVelocity = (newPosition - particle.GetPosition()) / m_dt;

    particle.SetPosition(newPosition);
    particle.SetVelocity(newVelocity);
    }
  }

void Fluid::_UpdateGrid()
  {
  for (auto& cell : m_grid.m_cells)
    cell.clear();
  for (auto& particle : m_particles)
    {
    const auto& position = particle.GetPosition();
    const auto& min_corner = m_bbox.GetMin();
    const auto& max_corner = m_bbox.GetMax();

    bool is_in_grid = true;
    for (int i = 0; i < 3; ++i)
      if (position[i] < min_corner[i] || position[i] > max_corner[i])
        {
        is_in_grid = false;
        break;
        }
    if (!is_in_grid)
      continue;

    const double delta_x = max_corner[0] - min_corner[0];
    const double delta_y = max_corner[1] - min_corner[1];
    const double delta_z = max_corner[2] - min_corner[2];

    std::size_t grid_id_x = static_cast<std::size_t>(m_grid.m_x * (position[0] - min_corner[0]) / delta_x);
    std::size_t grid_id_y = static_cast<std::size_t>(m_grid.m_y * (position[1] - min_corner[1]) / delta_y);
    std::size_t grid_id_z = static_cast<std::size_t>(m_grid.m_z * (position[2] - min_corner[2]) / delta_z);

    m_grid(grid_id_x, grid_id_y, grid_id_z).push_back(&particle);
    }
  }

bool Fluid::IntersectWithRay(IntersectionRecord& o_intersection, const Ray& i_ray) const
  {
  bool intersected = false;
  int i = 255;
  for (auto& particle : m_particles)
    {
    intersected |= Sphere(particle.GetPosition(), 0.5, std::make_shared<ColorMaterial>(Color(i))).IntersectWithRay(o_intersection, i_ray);
    i = 0x00ff00;
    }
  return intersected;
  }