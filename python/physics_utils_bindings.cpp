
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <astrokit/physics_utils.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

    void bind_physics_utils(py::module_& m)
    {
        //overloaded the exp_atmo function; need to use the overload_cast function in pybind11
        m.def("exp_atmo", py::overload_cast<double, double, double>(&exp_atmo),
              py::arg("alt"), py::arg("rho0"), py::arg("scale_height"),
              "Find density value using an exponential atmosphere model, explicitly providing the necessary inputs.");

        m.def("exp_atmo", py::overload_cast<double, const Planet&>(&exp_atmo),
              py::arg("alt"), py::arg("body"),
              "Find density value using an exponential atmosphere model, relying on astrokit's planetary constants values.");

        m.def("time_past_reference_epoch", &time_past_reference_epoch, py::arg("jd"), py::arg("ref_epoch") = 2451545.0,
              "Computes the time delta between the reference epoch (ref_epoch) and the specified Julian Date (jd). Returns a 3-element array of [seconds, centuries, days] <- for IAU coords.");

        m.def("mercury_ref_angles", &mercury_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("venus_ref_angles", &venus_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("earth_ref_angles", &earth_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("mars_ref_angles", &mars_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("jupiter_ref_angles", &jupiter_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("saturn_ref_angles", &saturn_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("uranus_ref_angles", &uranus_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        m.def("neptune_ref_angles", &neptune_ref_angles, py::arg("jd"),
            "Obtain the alpha0, delta0, & W reference angles for the IAU Cartographic Coords.");

        // note: leaving body_ref_angles() out of the bindings for now; really just meant as an internel helper
    }   
}