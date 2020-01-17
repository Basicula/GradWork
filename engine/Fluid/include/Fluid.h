#pragma once
#include <vector>

#include <IObject.h>
#include <BoundingBox.h>
#include <Particle.h>

class Ray;
struct Intersection;

class Fluid : public IObject
  {
  private:
    using Particles = std::vector<Particle>;
    using Cell = std::vector<Particle*>;

    struct Grid
      {
      std::size_t m_x;
      std::size_t m_y;
      std::size_t m_z;

      std::vector<Cell> m_cells;

      Grid(
        std::size_t x,
        std::size_t y,
        std::size_t z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
        , m_cells(x * y * z)
        {}

      inline Cell operator()(
        std::size_t i, 
        std::size_t j, 
        std::size_t k)
        {
        return m_cells[i + j * m_x + k * m_x * m_y];
        }

      std::vector<Particle*> GetNeigbourParticles(
        std::size_t x,
        std::size_t y,
        std::size_t z)
        {
        std::vector<Particle*> neighbours;
        for (int x_offset = -1; x_offset < 2; ++x_offset)
          {
          if (x + x_offset < 0)
            continue;
          if (x + x_offset > m_x)
            break;
          for (int y_offset = -1; y_offset < 2; ++y_offset)
            {
            if (y + y_offset < 0)
              continue;
            if (y + y_offset > m_y)
              break;
            for (int z_offset = -1; z_offset < 2; ++z_offset)
              {
              if (z + z_offset < 0)
                continue;
              if (z + z_offset > m_z)
                break;
              for (const auto& particle : (*this)(x + x_offset, y + y_offset, z + z_offset))
                neighbours.push_back(particle);
              }
            }
          }
        return neighbours;
        }
      };

  public:
    Fluid(const BoundingBox& i_box);

    virtual bool IntersectWithRay(
      IntersectionRecord& o_intersection,
      const Ray& i_ray) const override;
    virtual std::string Serialize() const override;
    virtual BoundingBox GetBoundingBox() const override;
    virtual void ApplyPhysics() override;

    static double GetTimeStep();

    std::size_t GetNumParticles() const;

  private:
    void _InitParticles();
    void _UpdatePositionAndVelocity();
    void _UpdateGrid();

    // workflow
    void _Step();
    void _UpdateDensityAndPressure();
    void _ComputeForcesForParticles();

    void _BruteForceStep();
    void _BruteUpdateDensityAndPressure();
    void _BruteComputeForcesForParticles();

  private:
    BoundingBox m_bbox;
    Grid m_grid;
    Particles m_particles;

    static const double m_dt;
  };

inline std::string Fluid::Serialize() const
  {
  std::string res = "{ \"Fluid\" : { ";
  res += "\"Box\" : " + m_bbox.Serialize();
  res += "} }";
  return res;
  }

inline BoundingBox Fluid::GetBoundingBox() const
  {
  return m_bbox;
  }

inline double Fluid::GetTimeStep()
  {
  return m_dt;
  }

inline void Fluid::ApplyPhysics()
  {
  _Step();
  //_BruteForceStep();
  }

inline std::size_t Fluid::GetNumParticles() const
  {
  return m_particles.size();
  }