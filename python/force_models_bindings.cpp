
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/force_models.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

	void bind_force_models(py::module_& m)
	{
        m.def("accel_kep", &accel_kep, py::arg("state"), py::arg("mu"),
              "Two-body acceleration: returns [v; a].");

        m.def("accel_j2", &accel_j2, py::arg("state"), py::arg("mu"), py::arg("Re"), py::arg("J2"),
              "J2-only perturbation acceleration. Returns [v; a], but want to just keep the accel components of the output.");
	}
}