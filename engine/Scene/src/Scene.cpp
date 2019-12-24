#include <Scene.h>

Scene::Scene(const std::string& i_name)
  : m_name(i_name)
  , m_active_camera(0)
  {}

bool Scene::RenderFrame(Image& o_image) const
  {
  return _Render(o_image, m_cameras[m_active_camera]);
  }

bool Scene::RenderCameraFrame(Image& o_image, std::size_t i_camera) const
  {
  if (i_camera >= m_cameras.size())
    return false;
  return _Render(o_image, m_cameras[i_camera]);
  }

bool Scene::_Render(Image& o_image, const Camera& i_camera) const
  {
  const auto& width = o_image.GetWidth();
  const auto& height = o_image.GetHeight();

  const auto& ray_origin = i_camera.GetLocation();

  for (auto x = 0u; x < width; ++x)
    for (auto y = 0u; y < height; ++y)
      {
      const auto& ray_dir = i_camera.GetDirection(1.0*x/width,1.0*y/height);
      Intersection hit;

      }
  return true;
  }