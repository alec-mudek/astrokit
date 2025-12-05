
#include <pybind11/pybind11.h>

namespace py = pybind11; //py is just as descreptive and I don't want to type it out every time

namespace astrokit_bindings 
{
    void bind_math_utils(py::module_& m);
    void bind_unit_structs(py::module_& m);
    void bind_constants(py::module_& m);
    void bind_rotations(py::module_& m);
    void bind_state_converter(py::module_& m);
    void bind_force_models(py::module_& m);
}

PYBIND11_MODULE(astrokit, m) 
{
    astrokit_bindings::bind_math_utils(m);
    astrokit_bindings::bind_unit_structs(m);
    astrokit_bindings::bind_constants(m);
    astrokit_bindings::bind_rotations(m);
    astrokit_bindings::bind_state_converter(m);
    astrokit_bindings::bind_force_models(m);
    //note: leaving integrators.h and propagator.h out of this; they're more complicated to make work w/pybind 
    //      and there are already plenty of options available in python for generic RK4 propagation functions
}
