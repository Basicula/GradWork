#pragma once
#include <vector>
#include <string>

#include <Color.h>

class Image
  {
  public:
    using ImageData = std::vector<std::vector<Color>>;
    using RawImageData = std::vector<uchar>;
    
    Image(
      std::size_t i_width, 
      std::size_t i_height, 
      const Color& i_default_color = Color(0));

    Color GetPixel(std::size_t i_x, std::size_t i_y) const;
    void SetPixel(std::size_t i_x, std::size_t i_y, const Color& i_color);

    std::size_t GetWidth() const;
    std::size_t GetHeight() const;
    std::size_t GetDepth() const;

    const ImageData& GetData() const;
    const RawImageData& GetRawData() const;
    const std::wstring& AsString() const;

  private:
    std::size_t m_width;
    std::size_t m_height;
    ImageData m_pixels;
    RawImageData m_raw_data;
    std::wstring m_string;

    static const uchar m_bytes_per_pixel = 3;
  };

inline Color Image::GetPixel(std::size_t i_x, std::size_t i_y) const
  {
  // TODO maybe change to throw
  if(i_x >= m_width || i_y >= m_height)
    return Color(0);
  return m_pixels[i_y][i_x];
  }

inline void Image::SetPixel(
  std::size_t i_x, 
  std::size_t i_y, 
  const Color& i_color)
  {
  if (i_x >= m_width || i_y >= m_height)
    return;
  m_pixels[i_y][i_x] = i_color;
  const auto pixel_id = (i_y * m_width + i_x) * m_bytes_per_pixel;
  m_raw_data[pixel_id + 0] = i_color.GetRed();
  m_raw_data[pixel_id + 1] = i_color.GetGreen();
  m_raw_data[pixel_id + 2] = i_color.GetBlue();

  m_string[pixel_id + 0] = i_color.GetRed();
  m_string[pixel_id + 1] = i_color.GetGreen();
  m_string[pixel_id + 2] = i_color.GetBlue();
  }

inline std::size_t Image::GetWidth() const
  {
  return m_width;
  }

inline std::size_t Image::GetHeight() const
  {
  return m_height;
  }
  
inline std::size_t Image::GetDepth() const
  {
  return m_bytes_per_pixel;
  }

inline const Image::ImageData& Image::GetData() const
  {
  return m_pixels;
  }

inline const Image::RawImageData& Image::GetRawData() const
  {
  return m_raw_data;
  }

inline const std::wstring& Image::AsString() const
  {
  return m_string;
  }