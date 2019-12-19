#pragma once
#include <vector>

#include <Color.h>

class Image
  {
  public:
    Image(std::size_t i_width, std::size_t i_height, const Color& i_default_color = Color(0));

    Color GetPixel(std::size_t i_x, std::size_t i_y) const;
    void SetPixel(std::size_t i_x, std::size_t i_y, const Color& i_color);

    std::size_t GetWidth() const;
    std::size_t GetHeight() const;

  private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<std::vector<Color>> m_pixels;
  };

inline Color Image::GetPixel(std::size_t i_x, std::size_t i_y) const
  {
  // TODO maybe change to throw
  if(i_x >= m_width || i_y >= m_height)
    return Color(0);
  return m_pixels[i_y][i_x];
  }

inline void Image::SetPixel(std::size_t i_x, std::size_t i_y, const Color& i_color)
  {
  if (i_x >= m_width || i_y >= m_height)
    return;
  m_pixels[i_y][i_x] = i_color;
  }

inline std::size_t Image::GetWidth() const
  {
  return m_width;
  }

inline std::size_t Image::GetHeight() const
  {
  return m_height;
  }