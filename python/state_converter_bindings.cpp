
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/state_converter.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

	void bind_state_converter(py::module_& m)
	{
        //note: all functions operate on Eigen::Vector<double, 6> and mu [km^3/s^2]

        m.def("cart_to_coe", &cart_to_coe, py::arg("cart"), py::arg("mu"),
              "Convert cartesian state [pos, vel] to classical orbital elements [a, e, i, raan, argp, ta].");

        m.def("coe_to_cart", &coe_to_cart, py::arg("coes"), py::arg("mu"),
              "Convert classical orbital elements [a, e, i, raan, argp, ta] to cartesian state [pos, vel].");

        m.def("cart_to_radec", &cart_to_radec, py::arg("cart"), 
              "Convert cartesian state [pos, vel] to spherical radec representation [R, raan, dec, V, vraan, vdec].");

        m.def("radec_to_cart", &radec_to_cart, py::arg("radec"), 
              "Convert spherical radec [R, raan, dec, V, vraan, vdec] to cartesian state [pos, vel].");

        m.def("coe_to_radec", &coe_to_radec, py::arg("coes"), py::arg("mu"), 
              "Convert classical orbital elements [a, e, i, raan, argp, ta] to spherical radec representation [R, raan, dec, V, vraan, vdec].");

        m.def("radec_to_coe", &radec_to_coe, py::arg("radec"), py::arg("mu"),
              "Convert spherical radec [R, raan, dec, V, vraan, vdec] representation to classical orbital elements [a, e, i, raan, argp, ta].");
	}
} // namespace astrokit_bindings