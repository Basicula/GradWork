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

Fluid::Fluid(const BoundingBox& i_box)
  : m_bbox(i_box)
  , m_simulation(256)
  {
  _InitParticles();
  }

void Fluid::_InitParticles()
  {
  auto& system = m_simulation.GetParticleSystem();
  auto particles_positions = system.GetPositions();
  const auto num_of_particles = system.GetNumOfParticles();
  for (int i = 0; i < num_of_particles; ++i)
    particles_positions[i] = Vector3d(-2 + i * SMOOTHING_RADIUS / 2, 1, 0);
  }

bool Fluid::IntersectWithRay(IntersectionRecord& o_intersection, const Ray& i_ray) const
  {
  bool intersected = false;
  auto& system = const_cast<SPHSimulation&>(m_simulation).GetParticleSystem();
  auto particles_positions = system.GetPositions();
  const auto num_of_particles = system.GetNumOfParticles();
  for (int i = 0; i < num_of_particles; ++i)
    {
    //TODO
    //intersected |= Sphere(
    //  particles_positions[i], 
    //  SMOOTHING_RADIUS, 
    //  std::make_shared<ColorMaterial>(Color(0xff0000))
    //  ).IntersectWithRay(o_intersection, i_ray);
    }
  return intersected;
  }