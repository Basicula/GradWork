#include <Image.h>

Image::Image(
  std::size_t i_width, 
  std::size_t i_height, 
  const Color& i_default_color)
  : m_width(i_width)
  , m_height(i_height)
  , m_pixels(i_height,std::vector<Color>(i_width, i_default_color))
  , m_raw_data(i_width * i_height * m_bytes_per_pixel, 0)
  , m_string(i_width* i_height* m_bytes_per_pixel, static_cast<uchar>(0))
  {}