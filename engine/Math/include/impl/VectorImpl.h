#pragma once
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <Vector.h>

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType>::Vector()
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] = 0;
  };
  
template<ull Dimension, class ElementType>
Vector<Dimension, ElementType>::Vector(ElementType i_elem)
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] = i_elem;
  };
  
template<ull Dimension, class ElementType>
template<ull D, typename T>
Vector<Dimension, ElementType>::Vector(ElementType i_x, ElementType i_y)
  {
  m_coords[0] = i_x;
  m_coords[1] = i_y;
  };

template<ull Dimension, class ElementType>
template<ull D, typename T>
Vector<Dimension, ElementType>::Vector(ElementType i_x, ElementType i_y, ElementType i_z)
  {
  m_coords[0] = i_x;
  m_coords[1] = i_y;
  m_coords[2] = i_z;
  };
  
template<ull Dimension, class ElementType>
template<ull D, typename T>
Vector<Dimension, ElementType>::Vector(ElementType i_x, ElementType i_y, ElementType i_z, ElementType i_w)
  {
  m_coords[0] = i_x;
  m_coords[1] = i_y;
  m_coords[2] = i_z;
  m_coords[3] = i_w;
  };

template<ull Dimension, class ElementType>
ElementType& Vector<Dimension, ElementType>::operator[](ull i_index)
  {
  if (i_index >= Dimension)
    throw std::out_of_range("Vector have smaller dimension");
  return m_coords[i_index];
  }

template<ull Dimension, class ElementType>
ElementType Vector<Dimension, ElementType>::operator[](ull i_index) const
  {
  if (i_index >= Dimension)
    throw std::out_of_range("Vector have smaller dimension");
  return m_coords[i_index];
  }
  
template<ull Dimension, class ElementType>
bool Vector<Dimension, ElementType>::operator==(const Vector<Dimension, ElementType>& i_other) const
  {
  bool equal = true;
  for (auto i = 0u; i < Dimension; ++i)
    {
      equal &= (m_coords[i] == i_other.m_coords[i]);
      if (!equal)
        break;
    }
  return equal;
  }
  
template<ull Dimension, class ElementType>
bool Vector<Dimension, ElementType>::operator!=(const Vector<Dimension, ElementType>& i_other) const
  {
  return !(*this == i_other);
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::operator-() const
  {
  Vector<Dimension,ElementType> copy(*this);
  for(auto& coord : copy.m_coords)
    coord = -coord;
  return copy;
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::operator-(const Vector<Dimension, ElementType>& i_other) const
  {
  Vector<Dimension, ElementType> copy(*this);
  copy -= i_other;
  return copy;
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType>& Vector<Dimension, ElementType>::operator-=(const Vector<Dimension, ElementType>& i_other)
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] -= i_other.m_coords[i];
  return *this;
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::operator+(const Vector<Dimension, ElementType>& i_other) const
  {
  Vector<Dimension, ElementType> copy(*this);
  copy += i_other;
  return copy;
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType>& Vector<Dimension, ElementType>::operator+=(const Vector<Dimension, ElementType>& i_other)
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] += i_other.m_coords[i];
  return *this;
  }

template<ull Dimension, class ElementType>
template<class Factor>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::operator*(Factor i_factor) const
  {
  Vector<Dimension, ElementType> copy(*this);
  copy *= i_factor;
  return copy;
  }

template<ull Dimension, class ElementType>
template<class Factor>
Vector<Dimension, ElementType>& Vector<Dimension, ElementType>::operator*=(Factor i_factor)
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] *= i_factor;
  return *this;
  }
  
template<ull Dimension, class ElementType>
template<class Factor>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::operator/(Factor i_factor) const
  {
  Vector<Dimension, ElementType> copy(*this);
  copy /= i_factor;
  return copy;
  }

template<ull Dimension, class ElementType>
template<class Factor>
Vector<Dimension, ElementType>& Vector<Dimension, ElementType>::operator/=(Factor i_factor)
  {
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] /= i_factor;
  return *this;
  }

template<ull Dimension, class ElementType>
double Vector<Dimension, ElementType>::Distance(const Vector<Dimension, ElementType>& i_other) const
  {
  return (*this - i_other).Length();
  }

template<ull Dimension, class ElementType>
inline ElementType Vector<Dimension, ElementType>::SquareDistance(const Vector & i_other) const
  {
  return (*this - i_other).SquareLength();
  }

template<ull Dimension, class ElementType>
template<ull D, typename T>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::CrossProduct(const Vector<Dimension, ElementType>& i_other) const
  {
  Vector<Dimension, ElementType> res;
  res.m_coords[0] = m_coords[1] * i_other.m_coords[2] - m_coords[2] * i_other.m_coords[1];
  res.m_coords[1] = m_coords[2] * i_other.m_coords[0] - m_coords[0] * i_other.m_coords[2];
  res.m_coords[2] = m_coords[0] * i_other.m_coords[1] - m_coords[1] * i_other.m_coords[0];
  return res;
  }

template<ull Dimension, class ElementType>
ElementType Vector<Dimension, ElementType>::Dot(const Vector<Dimension, ElementType>& i_other) const
  {
  ElementType res = 0;
  for (ull i = 0; i < Dimension; ++i)
    res += m_coords[i] * i_other.m_coords[i];
  return res;
  }

template<ull Dimension, class ElementType>
void Vector<Dimension, ElementType>::Normalize()
  {
  const double length = Length();
  for (ull i = 0; i < Dimension; ++i)
    m_coords[i] /= length;
  }

template<ull Dimension, class ElementType>
Vector<Dimension, ElementType> Vector<Dimension, ElementType>::Normalized() const
  {
  Vector<Dimension, ElementType> temp(*this);
  temp.Normalize();
  return temp;
  }

template<ull Dimension, class ElementType>
double Vector<Dimension, ElementType>::Length() const
  {
  return sqrt(SquareLength());
  }

template<ull Dimension, class ElementType>
ElementType Vector<Dimension, ElementType>::SquareLength() const
  {
  ElementType res = 0;
  for (ull i = 0; i < Dimension; ++i)
    res += m_coords[i] * m_coords[i];
  return res;
  }

template<ull Dimension, class ElementType>
std::string Vector<Dimension, ElementType>::Serialize() const
  {
  std::string res = "{ \"Vector" + std::to_string(m_dimension) + "d\" : [";
  for (auto i = 0u; i < m_dimension; ++i)
    {
    res += std::to_string(m_coords[i]);
    res += (i == m_dimension-1 ? "" : ", ");
    }
  res += "] }";
  return res;
  }