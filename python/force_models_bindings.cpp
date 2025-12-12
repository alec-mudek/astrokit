
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/force_models.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

	void bind_force_models(py::module_& m)
	{
        m.def("keplerian_dynamics", &keplerian_dynamics, py::arg("state"), py::arg("mu"),
              "Two-body acceleration: returns [v; a].");

        m.def("accel_j2", &accel_j2, py::arg("state"), py::arg("mu"), py::arg("Re"), py::arg("J2"),
              "J2-only perturbation acceleration. Returns just the accel components [ax, ay, az].");
        
        //overloaded the accel_drag function; needs special handling for bindings
        m.def("accel_drag", py::overload_cast<const Eigen::Vector<double, 6>&, double, double, double, double, const Eigen::Vector3d&>(&accel_drag),
            py::arg("state"), py::arg("m"), py::arg("Cd"), py::arg("A_m2"), py::arg("rho"), py::arg("omega_cb"), 
            "Returns the deceleration due to drag on a spacecraft.");

        m.def("accel_drag", py::overload_cast<const Eigen::Vector<double, 6>&, double, double, double, const Planet&>(&accel_drag),
            py::arg("state"), py::arg("m"), py::arg("Cd"), py::arg("A_m2"), py::arg("body"),
            "Returns the deceleration due to drag on a spacecraft.");

	}
}