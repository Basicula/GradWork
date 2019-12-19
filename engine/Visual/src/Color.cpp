#include <Color.h>

Color::Color()
  : m_rgb(0)
  {};

Color::Color(uint i_rgb)
  : m_rgb(i_rgb)
  {};

Color::Color(uchar i_red, uchar i_green, uchar i_blue)
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
  if (i_factor < 0)
    return Color();
  const uchar r = static_cast<uchar>(std::min(255.0, i_factor * GetRed())  );
  const uchar g = static_cast<uchar>(std::min(255.0, i_factor * GetGreen()));
  const uchar b = static_cast<uchar>(std::min(255.0, i_factor * GetBlue()) );
  return Color(r,g,b);
  }

Color Color::operator*(const Vector3d& i_factor) const
  {
  const uchar r = static_cast<uchar>(std::min(255.0, std::max(0.0, i_factor[0] * GetRed()))  );
  const uchar g = static_cast<uchar>(std::min(255.0, std::max(0.0, i_factor[1] * GetGreen())));
  const uchar b = static_cast<uchar>(std::min(255.0, std::max(0.0, i_factor[2] * GetBlue())) );
  return Color(r,g,b);
  }

Color Color::operator+(const Color & i_other) const
  {
  const uchar r = static_cast<uchar>(std::min(255, int(GetRed())   + int(i_other.GetRed())  ));
  const uchar g = static_cast<uchar>(std::min(255, int(GetGreen()) + int(i_other.GetGreen())));  
  const uchar b = static_cast<uchar>(std::min(255, int(GetBlue())  + int(i_other.GetBlue()) ));
  return Color(r, g, b);
  }
