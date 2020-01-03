#pragma once
#include <algorithm>

#include <Vector.h>

class BoundingBox
  {
  public:
    BoundingBox();
    BoundingBox(
      const Vector3d& i_min,
      const Vector3d& i_max);

    Vector3d GetMin() const;
    Vector3d GetMax() const;

    void AddPoint(const Vector3d& i_point);

    bool IsValid() const;

  private:
    Vector3d m_min;
    Vector3d m_max;
  };

inline Vector3d BoundingBox::GetMin() const
  {
  return m_min;
  }

inline Vector3d BoundingBox::GetMax() const
  {
  return m_max;
  }

inline bool BoundingBox::IsValid() const
  {
  return (m_min < m_max);
  }