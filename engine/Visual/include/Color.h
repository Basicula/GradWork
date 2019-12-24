#pragma once
#include <algorithm>
#include <string>

#include <Vector.h>

using uchar = unsigned char;
using uint = unsigned int;

class Color
{
public:
  Color();
  Color(uint i_rgb);
  Color(uchar i_red, uchar i_green, uchar i_blue);

  Color(const Color& i_other);

  Color operator*(double i_factor) const;
  Color operator*(const Vector3d& i_factor) const;
  Color operator+(const Color& i_other) const;

  bool operator==(const Color& i_other) const;
  bool operator!=(const Color& i_other) const;
  
  uchar GetRed()   const;
  uchar GetGreen() const;
  uchar GetBlue()  const;
  
  void SetRed(uchar i_red);
  void SetGreen(uchar i_green);
  void SetBlue(uchar i_blue);
  
  uint GetRGB() const;
  void SetRGB(uint i_rgb);

  std::string Serialize() const;
private:
  uint m_rgb;
};

inline uchar Color::GetRed() const
  {
  return static_cast<uchar>((m_rgb & 0xff0000) >> 16);
  }
  
inline uchar Color::GetGreen() const 
  { 
  return static_cast<uchar>((m_rgb & 0x00ff00) >> 8 ); 
  };
  
inline uchar Color::GetBlue() const 
  { 
  return static_cast<uchar>(m_rgb & 0x0000ff); 
  };
  
inline void Color::SetRed(uchar i_red)
  {
  m_rgb &= 0x00ffff;
  m_rgb |= (i_red << 16);
  }

inline void Color::SetGreen(uchar i_green)
  {
  m_rgb &= 0xff00ff;
  m_rgb |= (i_green << 8);
  }
  
inline void Color::SetBlue(uchar i_blue)
  {
  m_rgb &= 0xffff00;
  m_rgb |= i_blue;
  }
  
inline uint Color::GetRGB() const
  {
  return m_rgb;
  }
  
inline void Color::SetRGB(uint i_rgb)
  {
  m_rgb = i_rgb;
  }

inline std::string Color::Serialize() const
  {
  return "{ \"Color\" : " + std::to_string(m_rgb) + " }";
  }