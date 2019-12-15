#include <Scene.h>

static void AddScene(py::module& io_module)
  {
  py::class_<Scene>(io_module, "Scene")
    .def(py::init<std::string>(),
      py::arg("name") = "unnamed")
    .def_property("name",
      &Scene::GetName,
      &Scene::SetName);
  }