#pragma once
#include <vector>
#include <memory>
#include <string>

#include <IObject.h>
#include <ILight.h>
#include <Camera.h>

class Scene
  {
  public:
    Scene(const std::string& i_name = "Unnamed");

    void AddObject(IObject* i_object);
    void AddCamera(const Camera& i_camera, bool i_set_active = false);
    void AddLight(ILight* i_light);

    void ClearObjects();
    void ClearCameras();
    void ClearLights();

    bool SetActiveCamera(std::size_t i_id);

    bool SetOnOffLight(std::size_t i_id, bool i_state);

    std::string GetName() const;
    void SetName(const std::string& i_name);

  private:
    std::size_t m_active_camera;
    std::string m_name;
    std::vector<std::unique_ptr<IObject>> m_objcts;
    std::vector<Camera> m_cameras;
    std::vector<std::unique_ptr<ILight>> m_lights;
  };

inline void Scene::AddObject(IObject* i_object)
  {
  m_objcts.emplace_back(i_object);
  }

inline void Scene::AddCamera(const Camera& i_camera, bool i_set_active)
  {
  if (i_set_active)
    m_active_camera = m_cameras.size();
  m_cameras.push_back(i_camera);
  }

inline void Scene::AddLight(ILight* i_light)
  {
  m_lights.emplace_back(i_light);
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