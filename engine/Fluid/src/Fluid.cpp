#include <Fluid.h>
#include <DefinesAndConstants.h>
#include <FluidConstants.h>
#include <Sphere.h>
#include <ColorMaterial.h>
#include <RenderableObject.h>

Fluid::Fluid(const BoundingBox& i_box)
  : m_bbox(i_box)
  , m_simulation(25)
  {
  _InitParticles();
  }

void Fluid::_InitParticles()
  {
  auto& system = m_simulation.GetParticleSystem();
  auto particles_positions = system.GetPositions();
  const auto num_of_particles = system.GetNumOfParticles();
  for (int i = 0; i < num_of_particles; ++i)
    particles_positions[i] = Vector3d(
      static_cast<double>(rand()) / RAND_MAX,
      static_cast<double>(rand()) / RAND_MAX,
      static_cast<double>(rand()) / RAND_MAX);
  }

bool Fluid::IntersectWithRay(IntersectionRecord& o_intersection, const Ray& i_ray) const
  {
  bool intersected = false;
  auto& system = const_cast<SPHSimulation&>(m_simulation).GetParticleSystem();
  auto particles_positions = system.GetPositions();
  const auto num_of_particles = system.GetNumOfParticles();
  for (int i = 0; i < num_of_particles; ++i)
    {
    intersected |= RenderableObject(std::make_shared<Sphere>(
      particles_positions[i], 
      SMOOTHING_RADIUS), 
      std::make_shared<ColorMaterial>(Color(0x0000ff))
      ).IntersectWithRay(o_intersection, i_ray);
    }
  return intersected;
  }