#include <ColorMaterial.h>

namespace py = pybind11;

static void AddColor(py::module& io_module)
{
    py::class_<ColorMaterial>(io_module,"ColorMaterial")
        .def(py::init<Color,Vector3d,Vector3d,Vector3d,double,double,double>)
}