
#include <pybind11/pybind11.h>
#include <string>
#include <astrokit/constants.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

	void bind_constants(py::module_& m)
	{
		//start with the scalar constants 
        m.attr("MU_SUN") = MU_SUN;   // note: Mu object; will currently display in km^3/s^2
        m.attr("AU") = AU;       // note: Distance object; will currently display in km
        m.attr("PI") = PI;
        m.attr("DEG2RAD") = DEG2RAD;
        m.attr("RAD2DEG") = RAD2DEG;
        m.attr("DAY2SEC") = DAY2SEC;
        m.attr("YEAR2SEC") = YEAR2SEC;
        m.attr("SEC2DAY") = SEC2DAY;
        m.attr("SEC2YEAR") = SEC2YEAR;
        

        //now need to define our Planet struct
        py::class_<Planet>(m, "Planet")
            .def_readonly("ID", &Planet::ID)
            .def_readonly("MU", &Planet::MU)
            .def_readonly("R_MEAN", &Planet::R_MEAN)
            .def_readonly("R_EQUATOR", &Planet::R_EQUATOR)
            .def_readonly("R_POLE", &Planet::R_POLE)
            .def_readonly("SMA", &Planet::SMA)
            .def_readonly("ECC", &Planet::ECC)
            .def_readonly("INC", &Planet::INC)
            .def_readonly("T", &Planet::T)
            .def_readonly("T_SYNODIC", &Planet::T_SYNODIC)
            .def_readonly("J2", &Planet::J2)
            .def_readonly("SCALE_HEIGHT", &Planet::SCALE_HEIGHT)
            .def_readonly("SURFACE_DENSITY", &Planet::SURFACE_DENSITY)
            .def_readonly("SIDEREAL_ROTATION", &Planet::SIDEREAL_ROTATION)
            //still need a basic __repr__            
            .def("__repr__", [](const Planet&) { return std::string("<astrokit::Planet object>"); });

        // Planet singletons
        m.attr("MERCURY") = MERCURY;
        m.attr("VENUS") = VENUS;
        m.attr("EARTH") = EARTH;
        m.attr("MARS") = MARS;
        m.attr("JUPITER") = JUPITER;
        m.attr("SATURN") = SATURN;
        m.attr("URANUS") = URANUS;
        m.attr("NEPTUNE") = NEPTUNE;
	}
} // namespace astrokit_bindings
