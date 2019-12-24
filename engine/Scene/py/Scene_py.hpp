#include <Scene.h>

static void AddScene(py::module& io_module)
  {
  py::class_<Scene>(io_module, "Scene")
    .def(py::init<std::string>(),
      py::arg("name") = "unnamed")
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
    .def("__repr__", &Scene::Serialize);
  }