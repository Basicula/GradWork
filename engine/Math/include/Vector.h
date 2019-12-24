#pragma once

#include <type_traits>
#include <string>

using ull = unsigned long long;

template<ull Dimension = 3, class ElementType = double>
class Vector;

template<ull Dimension, class ElementType>
class Vector
  {
  public:
    template<ull D = Dimension, typename T = typename std::enable_if<D == 2>::type >
    Vector(ElementType i_x, ElementType i_y);
  
    template<ull D = Dimension, typename T = typename std::enable_if<D == 3>::type >
    Vector(ElementType i_x, ElementType i_y, ElementType i_z);
    
    template<ull D = Dimension, typename T = typename std::enable_if<D == 4>::type >
    Vector(ElementType i_x, ElementType i_y, ElementType i_z, ElementType i_w);

    Vector();
    Vector(ElementType i_elem);
    Vector(const Vector& i_other) = default;

    //can throw exception
    ElementType& operator[](ull i_index);
    ElementType operator[](ull i_index) const;
    
    bool operator==(const Vector& i_other) const;
    bool operator!=(const Vector& i_other) const;

    Vector operator-() const;
    Vector operator-(const Vector& i_other) const;
    Vector& operator-=(const Vector& i_other);

    Vector operator+(const Vector& i_other) const;
    Vector& operator+=(const Vector& i_other);

    template<class Factor>
    Vector operator*(Factor i_factor) const;
    template<class Factor>
    Vector& operator*=(Factor i_factor);
    
    template<class Factor>
    Vector operator/(Factor i_factor) const;
    template<class Factor>
    Vector& operator/=(Factor i_factor);

    template<ull D = Dimension, typename T = typename std::enable_if<D == 3>::type >
    Vector<Dimension, ElementType> CrossProduct(const Vector<Dimension, ElementType>& i_other) const;
    ElementType Dot(const Vector& i_other) const;
    void Normalize();
    Vector Normalized() const;
    double Length() const;
    ElementType SquareLength() const;
    double Distance(const Vector& i_other) const;
    ElementType SquareDistance(const Vector& i_other) const;

    std::string Serialize() const;
  protected:

  private:
    ElementType m_coords[Dimension];

  public:
    static const ull m_dimension = Dimension;
    using m_element_type = ElementType;
  };

#include <VectorImpl.h>

using Vector3d = Vector<3, double>;

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
  return Vector3d(m_coords[0]*i_val, m_coords[1] * i_val, m_coords[2] * i_val);
  }

template<>
template<>
inline Vector3d& Vector3d::operator*=<double>(double i_val)
  {
  m_coords[0] *= i_val;
  m_coords[1] *= i_val;
  m_coords[2] *= i_val;
  }

template<>
inline double Vector3d::SquareLength() const
  {
  return m_coords[0] * m_coords[0] + m_coords[1] * m_coords[1] + m_coords[2] * m_coords[2];
  }

template<>
inline double Vector3d::SquareDistance(const Vector3d& i_other) const
  {
  return (i_other - *this).SquareLength();
  }