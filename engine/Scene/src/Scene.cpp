#include <Scene.h>

Scene::Scene(const std::string& i_name)
  : m_name(i_name)
  , m_active_camera(0)
  {}