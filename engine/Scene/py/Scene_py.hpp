#include <memory>

#include <Scene.h>

static void AddScene(py::module& io_module)
  {
  py::class_<Scene, std::shared_ptr<Scene>>(io_module, "Scene")
    .def(py::init<
      const std::string&, 
      std::size_t, 
      std::size_t>(),
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
      py::arg("setActive") = false)
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
    .def("applyPhysics", &Scene::ApplyPhisics)
    .def_property(
      "frameWidth",
      &Scene::GetFrameWidth,
      &Scene::SetFrameWidth)
    .def_property(
      "frameHeight",
      &Scene::GetFrameHeight,
      &Scene::SetFrameHeight)
    .def("__repr__", &Scene::Serialize)
    .def("fromDict", [](py::dict i_dict)
      {
      auto scene = i_dict["Scene"];
      auto name = scene["Name"].cast<std::string>();
      auto frameWidth = scene["FrameWidth"].cast<std::size_t>();
      auto frameHeight = scene["FrameHeight"].cast<std::size_t>();
        
      Scene res(name,frameWidth,frameHeight);

      auto common_m = py::module::import("engine.Common");
      auto objects = scene["Objects"];
      for (auto object : objects)
        res.AddObject(common_m.attr("IObject").attr("fromDict")(object).cast<std::shared_ptr<IObject>>());

      auto light_m = py::module::import("engine.Visual.Light");
      auto lights = scene["Lights"];
      for (auto light : lights)
        res.AddLight(light_m.attr("ILight").attr("fromDict")(light).cast<std::shared_ptr<ILight>>());

      auto visual_m = py::module::import("engine.Visual");
      auto cameras = scene["Cameras"];
      for (auto camera : cameras)
        res.AddCamera(visual_m.attr("Camera").attr("fromDict")(camera).cast<Camera>());

      auto active_camera = scene["ActiveCamera"].cast<std::size_t>();
      res.SetActiveCamera(active_camera);

      return res;
      });
  }