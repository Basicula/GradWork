#include <algorithm>

#include <Scene.h>
#include <Ray.h>
#include <Intersection.h>
#include <ParallelUtils.h>
#include <ThreadPool.h>

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
  const auto width = o_image.GetWidth();
  const auto height = o_image.GetHeight();

  // temp needed for check when we need to know intersection 
  // but intrsection details don't interested for us
  IntersectionRecord temp;

  const auto& ray_origin = i_camera.GetLocation();
  ThreadPool::GetInstance()->ParallelFor(
    static_cast<std::size_t>(0),
    width * height,
    [&](std::size_t i_pixel_id)
    {
    auto x = i_pixel_id % width;
    auto y = i_pixel_id / width;
    const auto& ray_dir = i_camera.GetDirection(
      (x + i_offset_x) / m_frame_width,
      (y + i_offset_y) / m_frame_height);
    IntersectionRecord main_hit;
    main_hit.Reset();
    Ray ray(ray_origin, ray_dir);
    bool intersected = m_object_tree.IntersectWithRay(main_hit, ray);

    if (!intersected || !main_hit.m_material)
      {
      o_image.SetPixel(x, y, Color(0xaaccff));
      return;
      }

    Color result_pixel_color = main_hit.m_material->GetPrimitiveColor();

    // detect light influence
    std::size_t red, green, blue, active_lights_cnt;
    red = green = blue = active_lights_cnt = 0;
    for (auto i = 0u; i < m_lights.size(); ++i)
      {
      const auto& light = m_lights[i];
      if (!light->GetState())
        continue;
      ray.SetOrigin(main_hit.m_intersection);
      ray.SetDirection(-light->GetDirection(main_hit.m_intersection));
      if (!m_object_tree.IntersectWithRay(temp, ray))
        {
        ++active_lights_cnt;
        Color light_influence =
          main_hit.m_material->GetLightInfluence(
            main_hit.m_intersection,
            main_hit.m_normal,
            light);
        red += light_influence.GetRed();
        green += light_influence.GetGreen();
        blue += light_influence.GetBlue();
        }
      }
    if (active_lights_cnt > 0)
      {
      result_pixel_color += Color(
        static_cast<uchar>(red / active_lights_cnt),
        static_cast<uchar>(green / active_lights_cnt),
        static_cast<uchar>(blue / active_lights_cnt));
      }
    o_image.SetPixel(x, y, result_pixel_color);
    });
  return true;
  }

void Scene::Update()
  {
  for (auto& object : m_object_tree.GetObjects())
    object->Update();
  }