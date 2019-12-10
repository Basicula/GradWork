#include <Color.h>

Color::Color()
  : m_rgb(0)
  {};

Color::Color(uint i_rgb)
  : m_rgb(i_rgb)
  {};

Color::Color(unsigned char i_red, unsigned char i_green, unsigned char i_blue)
  : m_rgb(i_red << 16 | i_green << 8 | i_blue)
  {};

Color::Color(const Color& i_other)
  : m_rgb(i_other.m_rgb)
  {};

bool Color::operator==(const Color& i_other) const
  {
  return m_rgb == i_other.m_rgb;
  }
  
bool Color::operator!=(const Color& i_other) const
  {
  return m_rgb != i_other.m_rgb;
  }

Color Color::operator*(double i_factor) const
  {
  const uchar r = static_cast<uchar>(std::min(255.0,i_factor * Red())  );
  const uchar g = static_cast<uchar>(std::min(255.0,i_factor * Green()));
  const uchar b = static_cast<uchar>(std::min(255.0,i_factor * Blue()) );
  return Color(r,g,b);
  }

Color Color::operator*(const Vector3d& i_factor) const
  {
  const uchar r = static_cast<uchar>(std::min(255.0,i_factor[0] * Red())  );
  const uchar g = static_cast<uchar>(std::min(255.0,i_factor[1] * Green()));
  const uchar b = static_cast<uchar>(std::min(255.0,i_factor[2] * Blue()) );
  return Color(r,g,b);
  }

Color Color::operator+(const Color & i_other) const
  {
  const uchar r = static_cast<uchar>(std::min(255, int(Red())   + int(i_other.Red())  ));
  const uchar g = static_cast<uchar>(std::min(255, int(Green()) + int(i_other.Green())));  
  const uchar b = static_cast<uchar>(std::min(255, int(Blue())  + int(i_other.Blue()) ));
  return Color(r, g, b);
  }
