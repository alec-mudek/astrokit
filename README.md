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



These modules form the foundation for higher-level tools such as constellation simulators, navigation filter experiments, Monte‑Carlo analysis, and mission‑design workflows.

---

## 

## What’s Inside astrokit

### **Force Models**

* `accel\_kep` — Two-body Keplerian acceleration
* `accel\_j2` — J2‑perturbed gravitational model



### **Integrators**

* `rk4\_step` — Classic 4th‑order Runge–Kutta



### **Propagator**

* `propagator` — Wraps dynamics + integrator into a simple fixed‑step propagator



### **Coordinate \& Element Conversions**

* `cart\_to\_coe` — Cartesian → classical orbital elements
* `coe\_to\_cart` — Classical orbital elements → Cartesian



### **Rotation \& Geometry Tools**

* Axis-angle rotation matrices
* `lonlat\_to\_cart` — Geodetic → Cartesian



### **Math Utilities**

* `safe\_acos` — Numerically stable inverse cosine
* `random\_int`, `random\_double` — Uniform RNG helpers



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
astrokit::EARTH.SMA.au; //can also specify m or au units for Distances thanks to the Quantity templates in unit\\\\\\\_structs.h
astrokit::JUPITER.T; //Jupiter's orbital period (Time Quantity defaults to seconds)
astrokit::Jupiter.T.day; //can also specify different units with Time Quantities
astrokit::JUPITER.J2;

```

---



## Example: Converting a Cartesian State to COEs

```
#include <Eigen/Dense>
#include <astrokit/state\_converter.h>

// define a cartesian state
Eigen::Vector<double, 6> cartesian\_state;
cartesian\_state << x, y, z, vx, vy, vz;

// compute the classical orbital elements
Eigen::Vector<double, 6> coes = astrokit::cart\_to\_coe(cartesian\_state, mu\_central\_body);
```

# Example: Propagation of orbits.

An example usage of the integrator and propagator functions can be found in the test\_rk4\_prop.cpp script in the test/ folder.







