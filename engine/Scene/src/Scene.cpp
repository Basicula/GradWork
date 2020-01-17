#include <algorithm>

#include <Scene.h>
#include <Ray.h>
#include <Intersection.h>

Scene::Scene(
  const std::string& i_name,
  std::size_t i_frame_width,
  std::size_t i_frame_height)
  : m_name(i_name)
  , m_active_camera(0)
  , m_frame_width(i_frame_width)
  , m_frame_height(i_frame_height)
  {}

bool Scene::RenderFrame(
  Image& o_image,
  int i_offset_x,
  int i_offset_y) const
  {
  return _Render(
    o_image, 
    m_cameras[m_active_camera], 
    i_offset_x, 
    i_offset_y);
  }

bool Scene::RenderCameraFrame(
  Image& o_image, 
  std::size_t i_camera,
  int i_offset_x,
  int i_offset_y) const
  {
  if (i_camera >= m_cameras.size())
    return false;
  return _Render(
    o_image, 
    m_cameras[i_camera],
    i_offset_x,
    i_offset_y);
  }

bool Scene::_Render(
  Image& o_image, 
  const Camera& i_camera,
  double i_offset_x,
  double i_offset_y) const
  {
  const auto width   = o_image.GetWidth();
  const auto height  = o_image.GetHeight();

  const auto& ray_origin = i_camera.GetLocation();

  for (auto x = 0; x < width; ++x)
    for (auto y = 0; y < height; ++y)
      {
      const auto& ray_dir = i_camera.GetDirection((x+i_offset_x)/m_frame_width,(y+i_offset_y)/m_frame_height);
      const Ray ray(ray_origin,ray_dir);
      IntersectionRecord hit;
      bool intersected = m_object_tree.IntersectWithRay(hit, ray);

      if (!intersected  || !hit.m_material)
        {
        o_image.SetPixel(x, y, Color(0));
        continue;
        }

      Color result_pixel_color = hit.m_material->GetPrimitiveColor();

      std::vector<std::size_t> to_on;

      for (auto i = 0u; i < m_lights.size(); ++i)
        {
        auto& light = m_lights[i];
        if (!light->GetState())
          continue;
        Ray to_light(hit.m_intersection, -light->GetDirection(hit.m_intersection));
        IntersectionRecord temp;
        bool off = false;
        if (m_object_tree.IntersectWithRay(hit, ray))
          {
          light->SetState(false);
          to_on.push_back(i);
          off = true;
          break;
          }
        }
      result_pixel_color = result_pixel_color + hit.m_material->GetMultiLightInfluence(hit.m_intersection, hit.m_normal, m_lights);

      for (const auto& light_on : to_on)
        m_lights[light_on]->SetState(true);

      o_image.SetPixel(x,y, result_pixel_color);
      }
  return true;
  }

void Scene::ApplyPhysics()
  {
  for (auto& object : m_object_tree.GetObjects())
    object->ApplyPhysics();
  }