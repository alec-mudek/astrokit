# **astrokit**

**astrokit** is a lightweight, **header-only C++ astrodynamics library** providing core spacecraft-trajectory functionality for research, simulation, and rapid prototyping. It is designed to be:

* **Fast** — zero external dependencies beyond Eigen
* **Minimalistic** — focused on essential astrodynamics operations
* **Extensible** — easy to integrate into larger mission-design or navigation tools
* **Python-portable** — with optional pybind11 bindings in place for most components

---

## 

## Key Features at a Glance

* Two-body and J2 perturbed dynamics
* Fixed-step RK4 integrator
* Propagation module
* Cartesian, Classical Orbital Element, and Spherical RADEC conversions
* Rotation matrix utilities
* Planetary constants database with dimension handling
* Utility math functions (safe acos, random generators)
---

## 

## What’s Inside astrokit

### **Force Models**

* `accel_kep` — Two-body Keplerian acceleration
* `accel_j2` — J2‑perturbed gravitational model



### **Integrators**

* `rk4_step` — Classic 4th‑order Runge–Kutta



### **Propagator**

* `propagator` — Wraps dynamics + integrator into a simple fixed‑step propagator



### **Coordinate \& Element Conversions**

* `cart_to_coe` — Cartesian → classical orbital elements
* `coe_to_cart` — Classical orbital elements → Cartesian



### **Rotation \& Geometry Tools**

* Axis-angle rotation matrices
* `lonlat_to_cart` — Geodetic → Cartesian



### **Math Utilities**

* `safe_acos` - Numerically stable inverse cosine
* sign - Cpp implementation of the sign(x) function
* `angle_between_vecs, angle_between_vecs_w_direction, wrap_angle_diff, angular_distance_from_zero` - geometry utilities  
* `random_int`, `random_double` - Uniform RNG helpers



### **Planetary Constants**

A consolidated `Planet` struct giving access to:

* gravitational parameter
* mean/equatorial radius
* orbital elements
* rotation period
* J2



Example:

```
astrokit::EARTH.SMA; //distance units default to km
astrokit::EARTH.SMA.au; //can also specify m or au units for Distances thanks to the Quantity templates in unit_structs.h
astrokit::JUPITER.T; //Jupiter's orbital period (Time Quantity defaults to seconds)
astrokit::Jupiter.T.day; //can also specify different units with Time Quantities
astrokit::JUPITER.J2;

```

---



## Example: Converting a Cartesian State to COEs

```
#include <Eigen/Dense>
#include <astrokit/state_converter.h>

// define a cartesian state
Eigen::Vector<double, 6> cartesian_state;
cartesian_state << x, y, z, vx, vy, vz;

// compute the classical orbital elements
Eigen::Vector<double, 6> coes = astrokit::cart_to_coe(cartesian_state, mu_central_body);
```

# Example: Propagation of orbits.

An example usage of the integrator and propagator functions can be found in the test_rk4_prop.cpp script in the test/ folder.







