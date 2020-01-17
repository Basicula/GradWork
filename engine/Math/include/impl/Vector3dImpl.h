#pragma once

template<>
inline Vector3d Vector3d::operator-(const Vector3d& i_other) const
  {
  return Vector3d(m_coords[0] - i_other.m_coords[0], m_coords[1] - i_other.m_coords[1], m_coords[2] - i_other.m_coords[2]);
  }

template<>
inline Vector3d Vector3d::operator+(const Vector3d& i_other) const
  {
  return Vector3d(m_coords[0] + i_other.m_coords[0], m_coords[1] + i_other.m_coords[1], m_coords[2] + i_other.m_coords[2]);
  }

template<>
inline double Vector3d::Dot(const Vector3d& i_other) const
  {
  return m_coords[0] * i_other.m_coords[0] + m_coords[1] * i_other.m_coords[1] + m_coords[2] * i_other.m_coords[2];
  }

template<>
template<>
inline Vector3d Vector3d::operator*<double>(double i_val) const
  {
  return Vector3d(m_coords[0] * i_val, m_coords[1] * i_val, m_coords[2] * i_val);
  }

template<>
template<>
inline Vector3d& Vector3d::operator*=<double>(double i_val)
  {
  m_coords[0] *= i_val;
  m_coords[1] *= i_val;
  m_coords[2] *= i_val;
  return *this;
  }

template<>
inline double Vector3d::SquareLength() const
  {
  return  m_coords[0] * m_coords[0]
    + m_coords[1] * m_coords[1]
    + m_coords[2] * m_coords[2];
  }

template<>
inline double Vector3d::SquareDistance(const Vector3d& i_other) const
  {
  const double dx = i_other[0] - m_coords[0];
  const double dy = i_other[1] - m_coords[1];
  const double dz = i_other[2] - m_coords[2];
  return dx * dx + dy * dy + dz * dz;
  }

template<>
inline void Vector3d::Inverse()
  {
  m_coords[0] = 1 / m_coords[0];
  m_coords[1] = 1 / m_coords[1];
  m_coords[2] = 1 / m_coords[2];
  }

template<>
inline Vector3d Vector3d::Inversed() const
  {
  return Vector3d(
    1 / m_coords[0],
    1 / m_coords[1],
    1 / m_coords[2]);
  }

template<>
inline void Vector3d::Normalize()
  {
  const double length = Length();
  m_coords[0] /= length;
  m_coords[1] /= length;
  m_coords[2] /= length;
  }