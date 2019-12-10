#include <SpotLight.h>

namespace py = pybind11;

static void AddColor(py::module& io_module)
{
    py::class_<SpotLight>(io_module,"Color");
}