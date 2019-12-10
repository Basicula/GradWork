#include <ColorMaterial.h>

namespace py = pybind11;

static void AddColorMaterial(py::module& io_module)
{
    py::class_<ColorMaterial>(io_module,"ColorMaterial")
        .def(py::init<Color,Vector3d,Vector3d,Vector3d,double,double,double>())
        .def_property("ambient", 
                      &ColorMaterial::GetAmbient, 
                      &ColorMaterial::SetAmbient)
        .def_property("diffuse", 
                      &ColorMaterial::GetDiffuse, 
                      &ColorMaterial::SetDiffuse)
        .def_property("specular",
                      &ColorMaterial::GetSpecular,
                      &ColorMaterial::SetSpecular)
        .def_property("reflection", 
                      &ColorMaterial::GetReflection, 
                      &ColorMaterial::SetReflection)
        .def_property("refraction",
                      &ColorMaterial::GetRefraction,
                      &ColorMaterial::SetRefraction)
        .def("color",   &ColorMaterial::GetBaseColor)
        .def("acolor",  &ColorMaterial::GetAmbientColor)
        .def("dcolor",  &ColorMaterial::GetDiffuseColor)
        .def("scolor",  &ColorMaterial::GetSpecularColor);
}