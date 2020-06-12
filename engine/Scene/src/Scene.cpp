#include <algorithm>

#include <Scene.h>
#include <Ray.h>
#include <Intersection.h>
#include <ParallelUtils.h>
#include <ThreadPool.h>

IntersectionRecord Scene::m_dummy_intersection = IntersectionRecord();

Scene::Scene(
  const std::string& i_name,
  std::size_t i_frame_width,
  std::size_t i_frame_height)
  : m_name(i_name)
  , m_active_camera(static_cast<std::size_t>(-1))
  , m_frame_width(i_frame_width)
  , m_frame_height(i_frame_height)
  , m_rays()
  , m_intersection_records(m_frame_height* m_frame_width)
  {
  }

bool Scene::RenderFrame(
  Image& o_image,
  int i_offset_x,
  int i_offset_y)
  {
  if (m_active_camera == static_cast<std::size_t>(-1))
    throw "No active camera has been set";
  return _Render(
    o_image,
    m_active_camera,
    i_offset_x,
    i_offset_y);
  }

bool Scene::RenderCameraFrame(
  Image& o_image,
  std::size_t i_camera,
  int i_offset_x,
  int i_offset_y)
  {
  if (i_camera >= m_cameras.size())
    return false;
  return _Render(
    o_image,
    i_camera,
    i_offset_x,
    i_offset_y);
  }

bool Scene::_Render(
  Image& o_image,
  std::size_t i_camera,
  int i_offset_x,
  int i_offset_y)
  {
  // TODO : UPDATE THIS VERY BAD CODE)
  if (i_camera != m_active_camera)
    return false;
  ThreadPool::GetInstance()->ParallelFor(
    static_cast<std::size_t>(0),
    m_frame_width * m_frame_height,
    [&](std::size_t i_pixel_id)
    {
    auto x = i_pixel_id % m_frame_width + i_offset_x;
    auto y = i_pixel_id / m_frame_width + i_offset_y;
    o_image.SetPixel(x, y, _CastRay(i_pixel_id));
    });
  return true;
  }

void Scene::_UpdateRaysForActiveCamera()
  {
  m_rays.clear();
  const auto& camera = m_cameras[m_active_camera];

  const auto& ray_origin = camera.GetLocation();
  for(auto i = 0; i < m_frame_width * m_frame_height; ++i)
    {
    auto x = static_cast<double>(i % m_frame_width);
    auto y = static_cast<double>(i / m_frame_width);
    const auto& ray_dir = camera.GetDirection(
      x / m_frame_width,
      y / m_frame_height);
    m_rays.emplace_back(ray_origin, ray_dir);
    }
  }

Color Scene::_CastRay(std::size_t i_ray_id) 
  {
  auto& hit = m_intersection_records[i_ray_id];
  const auto& ray = m_rays[i_ray_id];

  hit.Reset();
  bool intersected = m_object_tree.IntersectWithRay(hit, ray);

  if (!intersected || !hit.m_material)
    return Color(0xaaccff);

  Color result_pixel_color = hit.m_material->GetPrimitiveColor();

  // detect light influence
  std::size_t red, green, blue, active_lights_cnt;
  red = green = blue = active_lights_cnt = 0;
  Ray to_light(hit.m_intersection, Vector3d(0, 1, 0));
  for (auto i = 0u; i < m_lights.size(); ++i)
    {
    const auto& light = m_lights[i];
    if (!light->GetState())
      continue;
    to_light.SetDirection(-light->GetDirection(hit.m_intersection));
    if (!m_object_tree.IntersectWithRay(m_dummy_intersection, to_light))
      {
      ++active_lights_cnt;
      Color light_influence =
        hit.m_material->GetLightInfluence(
          hit.m_intersection,
          hit.m_normal,
          light);
      red += light_influence.GetRed();
      green += light_influence.GetGreen();
      blue += light_influence.GetBlue();
      }
    }
  if (active_lights_cnt > 0)
    {
    result_pixel_color += Color(
      static_cast<std::uint8_t>(red / active_lights_cnt),
      static_cast<std::uint8_t>(green / active_lights_cnt),
      static_cast<std::uint8_t>(blue / active_lights_cnt));
    }
  return result_pixel_color;
  }

void Scene::Update()
  {
  m_object_tree.Update();
  }