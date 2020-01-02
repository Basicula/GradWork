#include <limits>

#include <BoundingBox.h>

BoundingBox::BoundingBox()
  : m_min(std::numeric_limits<int>::max())
  , m_max(std::numeric_limits<int>::min())
  {}

void BoundingBox::AddPoint(const Vector3d& i_point)
  {
  for (auto i = 0; i < 3; ++i)
    {
    m_min[i] = std::min(m_min[i], i_point[i]);
    m_max[i] = std::max(m_max[i], i_point[i]);
    }
  }