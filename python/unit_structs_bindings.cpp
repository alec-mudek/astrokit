
#include <pybind11/pybind11.h>
#include <astrokit/unit_structs.h>

namespace py = pybind11;

namespace astrokit_bindings
{
    using namespace astrokit;

	void bind_unit_structs(py::module_& m)
	{
		//note: for now I'm leaving the Quantity structs out and just binding the Distance, Time, Angle, and Mu structs
		//also note: structs are basically just tiny classes to python
		py::class_<Distance>(m, "Distance")
            .def_readonly("km", &Distance::km)
			.def_readonly("m", &Distance::m)
            .def_readonly("au", &Distance::au)

			//to reproduce the default-to-km behavior:
			.def("__float__", [](const Distance& d) { return d.km; }) //python equivalent of double() 
            
            //we also need to define operators (cpp automatically applies double() when you say astrokit.EARTH.SMA; python does not)
            .def("__add__", [](const Distance& d, double x) { return d.km + x; })
            .def("__sub__", [](const Distance& d, double x) { return d.km - x; })
            .def("__mul__", [](const Distance& d, double x) { return d.km * x; })
            .def("__truediv__", [](const Distance& d, double x) { return d.km / x; })

			//lastly, want to specify how the struct displays to the console
			.def("__repr__", [](const Distance& d) { return "<astrokit::Distance " + std::to_string(d.km) + " km>"; });
			//note: since we're not defining a __str__ method here, the __repr__ will be used both for standard representation 
			//		of the variable (when simply typing "d" in the python console) as well as for printing to the screen

        //now repeat for Time, Angle, and Mu
        py::class_<Time>(m, "Time")
            .def_readonly("sec", &Time::sec)
            .def_readonly("min", &Time::min)
            .def_readonly("hr", &Time::hr)
            .def_readonly("day", &Time::day)
            .def_readonly("yr", &Time::yr)
            .def("__float__", [](const Time& t) { return t.sec; })
            .def("__add__", [](const Time& t, double x) { return t.sec + x; })
            .def("__sub__", [](const Time& t, double x) { return t.sec - x; })
            .def("__mul__", [](const Time& t, double x) { return t.sec * x; })
            .def("__truediv__", [](const Time& t, double x) { return t.sec / x; })
            .def("__repr__", [](const Time& t) { return "<astrokit::Time " + std::to_string(t.sec) + " s>"; });

        py::class_<Angle>(m, "Angle")
            .def_readonly("deg", &Angle::deg)
            .def_readonly("rad", &Angle::rad)
            //note: Angles are constructed with a value in degrees as input but default to printing radians as output.
            //      if this causes confusion I will change it. for now, I'm mirroring my most common use cases for angles
            .def("__float__", [](const Angle& a) { return a.rad; })
            .def("__add__", [](const Angle& a, double x) { return a.rad + x; })
            .def("__sub__", [](const Angle& a, double x) { return a.rad - x; })
            .def("__mul__", [](const Angle& a, double x) { return a.rad * x; })
            .def("__truediv__", [](const Angle& a, double x) { return a.rad / x; })
            .def("__repr__", [](const Angle& a) { return "<astrokit::Angle " + std::to_string(a.rad) + " rad>"; });
            //hopefully the __repr__ will help avoid confusion w/the mixed units for construction vs default output

        py::class_<Mu>(m, "Mu")
            .def_readonly("km3_s2", &Mu::km3_s2)
            .def_readonly("m3_s2", &Mu::m3_s2)
            .def("__float__", [](const Mu& mu) { return mu.km3_s2; })
            .def("__add__", [](const Mu& mu, double x) { return mu.km3_s2 + x; })
            .def("__sub__", [](const Mu& mu, double x) { return mu.km3_s2 - x; })
            .def("__mul__", [](const Mu& mu, double x) { return mu.km3_s2 * x; })
            .def("__truediv__", [](const Mu& mu, double x) { return mu.km3_s2 / x; })
            .def("__repr__", [](const Mu& mu) { return "<Mu " + std::to_string(mu.km3_s2) + " km^3/s^2>"; });
	}
} // namespace astrokit_bindings