
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/math_utils.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

    void bind_math_utils(py::module_& m)
    {
        m.def("safe_acos", &safe_acos, py::arg("x"), "Clamps to -1.0 <= x <= 1.0 then computes the acos.");
        m.def("sign", &sign, py::arg("x"), "Returns -1, 0, or +1 if x is <0, =0, or >0, respectively.");
        m.def("angle_between_vecs", &angle_between_vecs, py::arg("vec1"), py::arg("vec2"), "Returns a simple angle calculation between two vectors (between [0, pi])");
        m.def("angle_between_vecs_w_direction", &angle_between_vecs_w_direction, py::arg("vec1"), py::arg("vec2"), py::arg("ref_axis"),
            "Returns the counterclockwise angle between two vectors; direction based on the reference axis.");
        m.def("wrap_angle_diff", &wrap_angle_diff, py::arg("angle1"), py::arg("angle2"), "Subtracts angle1 from angle2 and wraps the result to be in [0, 2pi].");
        m.def("angular_distance_from_zero", &angular_distance_from_zero, py::arg("angle"), "Function to provide the angular magnitude away from zero for a given angle. E.g. 3pi/2 becomes pi/2.");
        m.def("random_int", &random_int, py::arg("min"), py::arg("max"), "Returns a random integer in the range [min, max].");
        m.def("random_double", &random_double, py::arg("min"), py::arg("max"), "Returns a random double in the range [min, max].");
        m.def("sind", &sind, py::arg("angle"), "Sine function for input angle in degrees instead of radians.");
        m.def("cosd", &cosd, py::arg("angle"), "Cosine function for input angle in degrees instead of radians.");
    }
} // namespace astrokit_bindings