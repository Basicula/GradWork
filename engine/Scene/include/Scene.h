#pragma once
#include <vector>
#include <memory>
#include <string>

#include <IObject.h>
#include <ILight.h>
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
    // TODO create K-d tree
    std::vector<std::shared_ptr<IObject>> m_objcts;
    std::vector<Camera> m_cameras;
    std::vector<std::shared_ptr<ILight>> m_lights;
  };

inline void Scene::AddObject(std::shared_ptr<IObject> i_object)
  {
  m_objcts.push_back(i_object);
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
  return m_objcts.size();
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
  m_objcts.clear();
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
  for (auto i = 0u; i < m_objcts.size(); ++i)
    res += m_objcts[i]->Serialize() + (i == m_objcts.size() - 1 ? " ], " : ", ");
  res += "\"Cameras\" : [ ";
  for (auto i = 0u; i < m_cameras.size(); ++i)
    res += m_cameras[i].Serialize() + (i == m_cameras.size() - 1 ? " ], " : ", ");
  res += "\"Lights\" : [ ";
  for (auto i = 0u; i < m_lights.size(); ++i)
    res += m_lights[i]->Serialize() + (i == m_lights.size() - 1 ? " ], " : ", ");
  res += "\"ActiveCamera\" : " + std::to_string(m_active_camera);
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