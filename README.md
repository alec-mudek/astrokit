# **astrokit**

**astrokit** is a lightweight, **header-only C++ astrodynamics library** that provides core trajectory tools: force models, integrators, propagators, coordinate conversions, mathematical utilities, and planetary constants.



The library is built on top of **Eigen** (header-only linear algebra).  
Eigen is **not included** in this repository and must be installed separately.

---



## **Installation**

### 1\. Install Eigen

Download Eigen from the official source:

* **Getting Started:**  
  https://libeigen.gitlab.io/eigen/docs-nightly/GettingStarted.html
* **Downloads:**  
  https://libeigen.gitlab.io/

Eigen is header-only — simply place it in your `include/` directory or point your compiler to its path.

---

### 2\. Add astrokit to your include path

Clone this repo and add the `include/` directory to your compiler’s include paths:

```bash
-I path/to/astrokit/include
```

You do **not** need to build or link anything.  
Just include the headers you need.

---



## **Example Usage: Convert a Cartesian State to COEs**


#include <Eigen/Dense>
#include <astrokit/state\_converter.h>

// define a cartesian state
Eigen::Vector<double, 6> cartesian\_state;
cartesian\_state << x, y, z, vx, vy, vz;


// and use astrokit's cart\_to\_coe function to compute the COEs
Eigen::Vector<double, 6> coes =
    astrokit::cart\_to\_coe(cartesian\_state, mu\_central\_body);
---

## 

## **Modules and Features**

### **constants.h**

* Fundamental constants (AU, PI, MU\_SUN, DEG2RAD, etc.)
* Planetary constants using the `Planet` struct:
    struct Planet {
        double MU\_km3\_s2;
        double R\_MEAN\_km;
        double R\_EQUATOR\_km;
        double SMA\_km;
        double ECC\_deg;
        double INC\_deg;
        double T\_days;
        double J2;
    };
  
* Access example:

&nbsp; astrokit::EARTH.MU\_km3\_s2;
  astrokit::JUPITER.J2;


### **force\_models.h**

* `accel\_kep` — Two-body Keplerian acceleration model
* `accel\_j2` — **J2-only** gravitational perturbation



### **integrators.h**

* `rk4\_step` — Classic fixed-step 4th-order Runge–Kutta integrator



### **propagator.h**

* `propagator` — Simple fixed-step time propagation



### **math\_utils.h**

* `safe\_acos` — Numerically stable acos()
* `random\_int` — Uniform random integer
* `random\_double` — Uniform random double



### **rotations.h**

* Axis-angle rotation matrices
* `lonlat\_to\_cart` conversion



### **state\_converter.h**

* `cart\_to\_coe` and `coe\_to\_cart` transformations



## **Testing**

Includes Boost Odeint comparison tests validating:

* Keplerian propagation
* J2-perturbed propagation



## **Directory Structure**

astrokit/

|

|--include/astrokit/

|   |--constants.h

|   |--force\_models.h

|   |--integrators.h

|   |--propagator.h

|   |--math\_utils.h

|   |--rotations.h

|   |--state\_converter.h

|

|--tests/

|   |--test\_rk4\_prop.cpp

|\_\_\_

