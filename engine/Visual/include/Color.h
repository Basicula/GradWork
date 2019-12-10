#pragma once
#include <algorithm>

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
  
  inline uchar Red()    const { return static_cast<uchar>((m_rgb & 0xff0000) >> 16); };
  inline uchar Green()  const { return static_cast<uchar>((m_rgb & 0x00ff00) >> 8 ); };
  inline uchar Blue()   const { return static_cast<uchar>((m_rgb & 0x0000ff) >> 0 ); };
private:
  uint m_rgb;
};