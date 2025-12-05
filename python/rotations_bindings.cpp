
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/rotations.h>

namespace py = pybind11;

namespace astrokit_bindings
{
	using namespace astrokit;

	void bind_rotations(py::module_& m)
	{
		//unit vectors
		m.attr("i_hat") = i_hat;
		m.attr("j_hat") = j_hat;
		m.attr("k_hat") = k_hat;

        //rotation functions
        m.def("arbitrary_axis_rotation", &arbitrary_axis_rotation, py::arg("angle"), py::arg("axis"),
              "Return a 3x3 rotation matrix for a rotation of `angle` radians about the given axis.");

        m.def("x_rotation", &x_rotation, py::arg("angle"), "Rotation matrix for a rotation about the x-axis.");

        m.def("y_rotation", &y_rotation, py::arg("angle"), "Rotation matrix for a rotation about the y-axis.");

        m.def("z_rotation", &z_rotation, py::arg("angle"), "Rotation matrix for a rotation about the z-axis.");

		//lat-lon conversion
		m.def("lonlat_to_cart", &lonlat_to_cart, py::arg("lon"), py::arg("lat"), 
			  "Rotation matrix from planet-fixed lon/lat to Cartesian coordinates (angles in radians).");
	}
} // namespace astrokit_bindings