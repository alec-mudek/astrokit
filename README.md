# astrokit

Header-only C++ library with core astrodynamics functions. Built using the Eigen library, which is not included in this repo.



A getting started guide for Eigen can be found here: https://libeigen.gitlab.io/eigen/docs-nightly/GettingStarted.html



You can download Eigen here: https://libeigen.gitlab.io/



Eigen is also a header-only library, so once the files are downloaded and in your include path, you are ready to use astrokit.

Similar to Eigen, astrokit simply needs to be downloaded and the include/ directory in this repo must be in your include path.

This library uses the astrokit namespace throughout. An example usage:



\#include <astrokit/state\_converter.h>

//example use case: convert cartesian state to orbital elements

Eigen::Matrix<double, 6, 1> cartesian\_state;

cartesian\_state << x, y, z, vx, vy, vz;

Eigen::Matrix<double, 6, 1> coes = astrokit::cart\_to\_coe(cartesian\_state, mu\_central\_body);



Test scripts and example scripts will be added to the repo soon.





Current astrokit scripts \& functions:



-constants.h

    -Basic constants like 1 AU, PI, MU\_SUN

    -Planetary constants stored in a Planet struct

 	struct Planet

 	{

            double MU\_km3\_s2;

            double R\_MEAN\_km;

            double SMA\_km;

            double ECC\_deg;

            double INC\_deg;

            double T\_days;

            double J2;

    	};

    -Each planet has its own Planet struct with access to the specified parameters: EARTH::MU\_km3\_s2, URANUS::SMA\_km, etc.



-force\_models.h

    -accel\_kep: Keplerian, two-body equations of motion. Accepts a state and mu value and returns dstate/dt.

    -accel\_j2: J2 perturbations only. Doesn't include any central body acceleration; must also include an AccelKep (or other)

 	      call for that. Accepts a state, mu, equatorial radius, and J2 value; returns dstate/dt.



-integrators.h

    -rk4\_step: Simple, fixed-step, 4th-order Runge Kutta implementation. Uses the standard Butcher Tableau.



-propagator.h

    -propagator: Simple, fixed step propagation that can handle forward \& backwards prop. Returns both a state history and a

 		 time history over the propagation.



-math\_utils.h

    -safe\_acos: Arccos computation with clamped input value to make sure machine precision or roundoff error doesn't result in a

 	        value outside of -1.0 < x < 1.0 when acos(x) is computed.

    -random\_int: Returns a random integer between some lower \& upper bounds.

    -random\_double: Returns a random double between some lower \& upper bounds.



-rotations.h

    -x\_rotation: Returns the rotation matrix for a rotation about the x-axis.

    -y\_rotation: Returns the rotation matrix for a rotation about the y-axis.

    -z\_rotation: Returns the rotation matrix for a rotation about the z-axis.

    -lonlat\_to\_cart: Returns a rotation matrix to convert longitude + latitude to cartesian coordinates.



-state\_converter.h

    -cart\_to\_coe: Computes the Classical Orbital Elements of a user-provided cartesian state and central body gravitational parameter.

    -coe\_to\_cart: Computes the cartesian state of a user-provided COEs and central body gravitational parameter.





