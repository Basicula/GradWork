#include <Camera_py.hpp>
#include <Color_py.hpp>
#include <ColorMaterial_py.hpp>
#include <SpotLight_py.hpp>

static void AddVisualSubmodule(py::module& io_module)
  {
  auto visual_submodule = io_module.def_submodule("Visual");
  AddCamera(visual_submodule);
  AddColor(visual_submodule);
  AddColorMaterial(visual_submodule);
  AddLight(visual_submodule);
  }