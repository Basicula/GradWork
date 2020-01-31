#include <BFPointSearcher.h>
#include <SPHSystem.h>
#include <SPHStandartKernel.h>
#include <ParallelUtils.h>

SPHSystem::SPHSystem(
  std::size_t i_num_particles,
  double i_system_density,
  double i_radius,
  double i_mass)
  : ParticleSystem(i_num_particles)
  , m_system_density(i_system_density)
  , m_radius(i_radius)
  , m_mass(i_mass)
  , mp_neighbor_searcher(nullptr)
  , m_neighbors_list(i_num_particles)
  {
  m_positions_id = AddVectorData();
  m_velocities_id = AddVectorData();
  m_forces_id = AddVectorData();

  m_densities_id = AddScalarData();
  m_pressures_id = AddScalarData();
  }

void SPHSystem::BuildNeighborSearcher()
  {
  mp_neighbor_searcher = std::make_shared<BFPointSearcher>(
    _GetVectorDataAt(m_positions_id), m_num_particles);
  }

void SPHSystem::BuildNeighborsList()
  {
  auto points = GetPositions();
  for (auto i = 0u; i < m_num_particles; ++i)
    {
    const Vector3d& origin = points[i];
    m_neighbors_list[i].clear();

    mp_neighbor_searcher->ForEachNearbyPoint(
      origin,
      m_radius,
      [&](std::size_t j, const Vector3d&)
      {
      if (i != j)
        {
        m_neighbors_list[i].push_back(j);
        }
      });
    }
  }

void SPHSystem::UpdateDensities()
  {
  auto positions = GetPositions();
  auto densities = GetDensities();

  Parallel::ParallelFor(
    static_cast<std::size_t>(0), 
    m_num_particles, 
    [&](std::size_t i)
    {
    double sum = _SumOfKernelsNearby(positions[i]);
    densities[i] = m_mass * sum;
    });
  }

double SPHSystem::_SumOfKernelsNearby(const Vector3d& i_origin) const
  {
  double sum = 0.0;
  const SPHStandartKernel kernel(m_radius);
  mp_neighbor_searcher->ForEachNearbyPoint(
    i_origin, 
    m_radius, 
    [&](std::size_t, const Vector3d& i_neighbor)
    {
    double dist = i_origin.SquareDistance(i_neighbor);
    sum += kernel(dist);
    });
  return sum;
  }