#pragma once
#include <vector>
#include <memory>
#include <string>

#include <KDTree.h>
#include <ILight.h>
#include <IMaterial.h>
#include <Camera.h>
#include <Image.h>

class Scene
  {
  public:
    Scene(
      const std::string& i_name = "Unnamed", 
      std::size_t i_frame_width = 800, 
      std::size_t i_frame_height = 600);

    void AddObject(std::shared_ptr<IObject> i_object);
    void AddCamera(const Camera& i_camera, bool i_set_active = false);
    void AddLight(std::shared_ptr<ILight> i_light);

    std::size_t GetNumObjects() const;
    std::size_t GetNumLights() const;
    std::size_t GetNumCameras() const;

    void ClearObjects();
    void ClearCameras();
    void ClearLights();

    bool SetActiveCamera(std::size_t i_id);

    bool SetOnOffLight(std::size_t i_id, bool i_state);

    std::string GetName() const;
    void SetName(const std::string& i_name);

    std::size_t GetFrameWidth() const;
    void SetFrameWidth(std::size_t i_frame_width);
    std::size_t GetFrameHeight() const;
    void SetFrameHeight(std::size_t i_frame_height);

    bool RenderFrame(
      Image& o_image,
      int i_offset_x = 0,
      int i_offset_y = 0) const;
    bool RenderCameraFrame(
      Image& o_image, 
      std::size_t i_camera,
      int i_offset_x = 0,
      int i_offset_y = 0) const;

    void ApplyPhisics();

    std::string Serialize() const;
  private:
    bool _Render(
      Image& o_image, 
      const Camera& i_camera, 
      double i_offset_x, 
      double i_offset_y) const;

  private:
    std::size_t m_active_camera;
    std::string m_name;
    std::size_t m_frame_width;
    std::size_t m_frame_height;
    KDTree m_object_tree;
    std::vector<Camera> m_cameras;
    std::vector<std::shared_ptr<ILight>> m_lights;
  };

inline void Scene::AddObject(std::shared_ptr<IObject> i_object)
  {
  m_object_tree.AddObject(i_object);
  }

inline void Scene::AddCamera(const Camera& i_camera, bool i_set_active)
  {
  if (i_set_active)
    m_active_camera = m_cameras.size();
  m_cameras.push_back(i_camera);
  }

inline void Scene::AddLight(std::shared_ptr<ILight> i_light)
  {
  m_lights.push_back(i_light);
  }

inline std::size_t Scene::GetNumObjects() const
  {
  return m_object_tree.Size();
  }

inline std::size_t Scene::GetNumLights() const
  {
  return m_lights.size();
  }

inline std::size_t Scene::GetNumCameras() const
  {
  return m_cameras.size();
  }

inline bool Scene::SetActiveCamera(std::size_t i_id)
  {
  if (i_id < m_cameras.size())
    {
    m_active_camera = i_id;
    return true;
    }
  return false;
  }

inline std::string Scene::GetName() const
  {
  return m_name;
  }

inline void Scene::SetName(const std::string& i_name)
  {
  m_name = i_name;
  }

inline void Scene::ClearObjects()
  {
  m_object_tree.Clear();
  }

inline void Scene::ClearCameras()
  {
  m_cameras.clear();
  }

inline void Scene::ClearLights()
  {
  m_lights.clear();
  }

inline bool Scene::SetOnOffLight(std::size_t i_id, bool i_state)
  {
  if (i_id < m_lights.size())
    {
    m_lights[i_id]->SetState(i_state);
    return true;
    }
  return false;
  }

inline std::string Scene::Serialize() const
  {
  std::string res = "{ \"Scene\" : { ";
  res += "\"Name\" : \"" + m_name + "\", ";
  res += "\"Objects\" : [ ";
  const auto& objects = m_object_tree.GetObjects();
  const auto object_cnt = m_object_tree.Size();
  for (auto i = 0u; i < object_cnt; ++i)
    res += objects[i]->Serialize() + (i == object_cnt - 1 ? " ], " : ", ");
  res += "\"Cameras\" : [ ";
  const auto cameras_cnt = m_cameras.size();
  for (auto i = 0u; i < cameras_cnt; ++i)
    res += m_cameras[i].Serialize() + (i == cameras_cnt - 1 ? " ], " : ", ");
  res += "\"Lights\" : [ ";
  const auto lights_cnt = m_lights.size();
  for (auto i = 0u; i < lights_cnt; ++i)
    res += m_lights[i]->Serialize() + (i == lights_cnt - 1 ? " ], " : ", ");
  res += "\"ActiveCamera\" : " + std::to_string(m_active_camera) + ", ";
  res += "\"FrameWidth\" : " + std::to_string(m_frame_width) + ", ";
  res += "\"FrameHeight\" : " + std::to_string(m_frame_height);
  res += "} }";
  return res;
  }

inline std::size_t Scene::GetFrameWidth() const
  {
  return m_frame_width;
  }

inline void Scene::SetFrameWidth(std::size_t i_frame_width)
  {
  m_frame_width = i_frame_width;
  }

inline std::size_t Scene::GetFrameHeight() const
  {
  return m_frame_height;
  }

inline void Scene::SetFrameHeight(std::size_t i_frame_height)
  {
  m_frame_height = i_frame_height;
  }