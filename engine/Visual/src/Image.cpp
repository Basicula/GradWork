#include <Image.h>

Image::Image(
  std::size_t i_width, 
  std::size_t i_height, 
  const Color& i_default_color)
  : m_width(i_width)
  , m_height(i_height)
  , m_pixels(i_height,std::vector<Color>(i_width, i_default_color))
  {}