#include <memory>

#include <Scene.h>

static void AddScene(py::module& io_module)
  {
  py::class_<Scene, std::shared_ptr<Scene>>(io_module, "Scene")
    .def(py::init<std::string, std::size_t, std::size_t>(),
      py::arg("name") = "unnamed",
      py::arg("frameWidth") = 800,
      py::arg("frameHeight") = 600)
    .def_property("name",
      &Scene::GetName,
      &Scene::SetName)
    .def_property_readonly("objCnt", &Scene::GetNumObjects)
    .def_property_readonly("camCnt", &Scene::GetNumCameras)
    .def_property_readonly("lightCnt", &Scene::GetNumLights)
    .def("addObject", &Scene::AddObject)
    .def("addCamera", 
      &Scene::AddCamera,
      py::arg("camera"),
      py::arg("setActive") = true)
    .def("addLight", &Scene::AddLight)
    .def("clearObjects", &Scene::ClearObjects)
    .def("clearCameras", &Scene::ClearCameras)
    .def("clearLights", &Scene::ClearLights)
    .def("setActiveCamera", &Scene::SetActiveCamera)
    .def("setOnOffLight", &Scene::SetOnOffLight)
    .def(
      "getFrame", 
      &Scene::RenderFrame,
      py::arg("image"),
      py::arg("x_offset") = 0,
      py::arg("y_offset") = 0)
    .def_property(
      "frameWidth",
      &Scene::GetFrameWidth,
      &Scene::SetFrameWidth)
    .def_property(
      "frameHeight",
      &Scene::GetFrameHeight,
      &Scene::SetFrameHeight)
    .def("__repr__", &Scene::Serialize);
  }