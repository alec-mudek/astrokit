#pragma once

#include <Eigen/Dense>
#include <cmath>

#include "constants.h"
#include "physics_utils.h"

namespace astrokit 
{
    //note: The following accel functions can't be used directly with the rk4_step function in integrators.h
    //      since they aren't of the form f(t, y). The idea is these will be wrapped in an integration method 
    //      in whatever external script they are used (more modular & generic this way). See the file
    //      test_rk4_prop.cpp for example usage.

    //basic, two-body motion
    inline Eigen::Vector<double, 6> keplerian_dynamics(const Eigen::Vector<double, 6>& state, double mu)
    {
        Eigen::Vector3d r = state.segment<3>(0);
        Eigen::Vector3d v = state.segment<3>(3);

        const double R = r.norm();
        const double R3 = R * R * R;

        Eigen::Vector<double, 6> dstate_dt;
        dstate_dt << v, -mu * r / R3 ;

        return dstate_dt;
    }

    // J2 gravity perturbation for oblate spheroid, z-axis aligned with spin axis
    // note: ONLY returns the accel due to J2 perturbation; no central body gravity included
    inline Eigen::Vector3d accel_j2(const Eigen::Vector<double, 6>& state, double mu, double Re, double J2)
    {
        Eigen::Vector3d r = state.segment<3>(0);

        const double R1 = r.norm();
        const double R2 = R1 * R1;

        const double factor = 1.5 * J2 * mu * Re * Re / (R2 * R2 * R1);
        const double k = 5.0 * r(2) * r(2) / R2;

        Eigen::Vector3d a((r(0)) * (k - 1.0) * factor, (r(1)) * (k - 1.0) * factor, (r(2)) * (k - 3.0) * factor);

        return a;
    }

    // similar function for simple atmo drag
    inline Eigen::Vector3d accel_drag(const Eigen::Vector<double, 6>& state, double m, double Cd, double A_m2, double rho, const Eigen::Vector3d& omega_cb)
    {
        //assuming A is provided in m^2
        A /= 1e6;

        Eigen::Vector3d r = state.segment<3>(0);
        Eigen::Vector3d v = state.segment<3>(3);

        Eigen::Vector3d v_atm = omega_cb.cross(r);
        Eigen::Vector3d v_rel = v - v_atm;
        double V = v_rel.norm();

        Eigen::Vector3d a = -0.5 * Cd * A * rho * V * v_rel / m;
        
        return a;
    }

    // can take advantage of the resources available in astrokit
    // note: this function assumes an EXPONENTIAL ATMO model and a PERFECTLY SPHERICAL body
    inline Eigen::Vector3d accel_drag(const Eigen::Vector<double, 6>& state_km_kmps, double m, double Cd, double A_m2, const Planet& body)
    {
        //assuming A is provided in m^2; this is fixed (converted to km^2) in the accel_drag call below

        //need to unpack omega_cb & rho from the body struct
        Eigen::Vector3d r = state_km_kmps.segment<3>(0);

        double h = r.norm() - body.R_MEAN; //THIS LINE ASSUMES POSITION IN KM (unless default Distance unit in unit_structs.h changes)
        double rho = exp_atmo(h, body); //exponential atmosphere

        //also need omega - assuming perfectly corotating atmo here
        Eigen::Vector3d omega;
        omega << 0, 0, 2*PI / body.SIDEREAL_ROTATION.sec;

        Eigen::Vector3d a = accel_drag(state_km_kmps, m, Cd, A, rho, omega);

        return a;
    }

} // namespace astrokit
