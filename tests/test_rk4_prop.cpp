
// validate astrokit's rk4_step integrator & propagator functions against boost's odeint

#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <Eigen/Dense>
#include <boost/numeric/odeint.hpp>

#include <astrokit/constants.h>
#include <astrokit/force_models.h>
#include <astrokit/integrators.h>
#include <astrokit/propagator.h>

namespace odeint = boost::numeric::odeint;

// State types for boost & astrokit, respectively (don't feel like typing these every time)
using array_state = std::array<double, 6>;
using eig_state = Eigen::Vector<double, 6>;

//note: need to use arrays w/boost
//worth making conversion functions
array_state eigen_to_array(const eig_state& y)
{
    array_state a{};
    for (int i = 0; i < 6; ++i)
        a[i] = y(i);
    return a;
}

eig_state array_to_eigen(const array_state& a)
{
    eig_state y;
    for (int i = 0; i < 6; ++i)
        y(i) = a[i];
    return y;
}

//convenient structure for storing the boost state_history
struct odeint_history
{
    std::vector<double>     t;
    std::vector<array_state> y;

    void operator()(const array_state& state, double t_val)
    {
        t.push_back(t_val);
        y.push_back(state);
    }
};


int main()
{
    //going to propagate a spacecraft in LEO
    //need some constants
    const double mu = astrokit::EARTH.MU.km3_s2;
    const double Re = astrokit::EARTH.R_EQUATOR.km;
    const double J2 = astrokit::EARTH.J2;

    //arbitrarily picking a circular, 500km orbit
    const double alt_km = 500.0;
    const double r0 = Re + alt_km;

    eig_state y0_eigen;
    y0_eigen << r0, 0.0, 0.0,
        0.0, std::sqrt(mu / r0), 0.0;

    array_state y0_array = eigen_to_array(y0_eigen);

    // One orbital period for circular orbit: T = 2*pi*sqrt(a^3/mu)
    const double T = 2.0 * astrokit::PI * std::sqrt(r0 * r0 * r0 / mu);

    const double t0 = 0.0;
    const double tf = 86400.0;
    const double dt = 30.0;      // fixed step (s)

    //testing both keplerian & j2 EOMs
    //start with kep
    auto system_kep = [mu](const array_state& y, array_state& dydt, double /*t*/)
        {
            eig_state y_e = array_to_eigen(y);
            eig_state dy_e = astrokit::accel_kep(y_e, mu);
            for (int i = 0; i < 6; ++i)
                dydt[i] = dy_e(i);
        };

    odeint::runge_kutta4<array_state> rk4_boost;

    odeint_history hist_kep_boost;
    odeint::integrate_const(
        rk4_boost,
        system_kep,
        y0_array,
        t0,
        tf,
        dt,
        std::ref(hist_kep_boost)
    );

    //initial condition y0_array is changed through the function call; need to reinitialize for J2 prop
    array_state y0_array_j2 = eigen_to_array(y0_eigen);

    //now do j2
    auto system_kep_j2 = [mu, Re, J2](const array_state& y, array_state& dydt, double /*t*/)
        {
            eig_state y_e = array_to_eigen(y);

            // [v; a_kep]
            eig_state dy_kep = astrokit::accel_kep(y_e, mu);
            // [v; a_J2_only]; only want the accel term from this
            eig_state dy_j2 = astrokit::accel_j2(y_e, mu, Re, J2);

            // Combine accelerations; keep velocity derivative from Kepler term
            dy_kep.segment<3>(3) += dy_j2.segment<3>(3);

            for (int i = 0; i < 6; ++i)
                dydt[i] = dy_kep(i);
        };

    odeint_history hist_kep_j2_boost;
    odeint::integrate_const(
        rk4_boost,
        system_kep_j2,
        y0_array_j2,
        t0,
        tf,
        dt,
        std::ref(hist_kep_j2_boost)
    );

    
    //now do the same (kep then j2) for astrokit
    //need a force model function that matches the template f(t, y) for rk4_step
    auto f_kep = [mu](double /*t*/, const eig_state& y)
        {
            return astrokit::accel_kep(y, mu);
        };

    //also need to define a stepping method for the propagator
    auto step_kep = [f_kep](double t, double dt, const eig_state& y)
        {
            return astrokit::rk4_step(t, dt, y, f_kep);
        };

    //now propagate (astrokit returns the full state_history, including time span)
    auto hist_kep_astro = astrokit::propagator(t0, dt, tf, y0_eigen, step_kep);

    //repeat for j2
    auto f_kep_j2 = [mu, Re, J2](double /*t*/, const eig_state& y)
        {
            eig_state dy_kep = astrokit::accel_kep(y, mu);
            eig_state dy_j2 = astrokit::accel_j2(y, mu, Re, J2);

            dy_kep.segment<3>(3) += dy_j2.segment<3>(3);
            return dy_kep;
        };

    auto step_kep_j2 = [f_kep_j2](double t, double dt, const eig_state& y)
        {
            return astrokit::rk4_step(t, dt, y, f_kep_j2);
        };

    auto hist_kep_j2_astro = astrokit::propagator(t0, dt, tf, y0_eigen, step_kep_j2);


    //have the full histories for both keplerian & j2-perturbed trajectories from both astrokit & boost odeint
    //make sure both solutions are in agreement for both force models
    auto compare_histories = [](const odeint_history& boost_hist,
        const astrokit::StateHistory<eig_state>& astro_hist,
        const double tolerance, const std::string& label)
        {
            std::size_t n_boost = boost_hist.t.size();
            std::size_t n_astro = astro_hist.t.size();

            if (n_boost != n_astro)
            {
                std::cerr << "Size mismatch for " << label
                    << ": boost has " << n_boost
                    << " points, astrokit has " << n_astro << " points.\n";
            }

            std::size_t n = std::min(n_boost, n_astro);

            double max_pos_err = 0.0;
            double max_vel_err = 0.0;
            double max_time_diff = 0.0;

            for (std::size_t i = 0; i < n; ++i)
            {
                double t_b = boost_hist.t[i];
                double t_a = astro_hist.t[i];
                max_time_diff = std::max(max_time_diff, std::abs(t_b - t_a));

                eig_state y_a = astro_hist.y[i];
                eig_state y_b = array_to_eigen(boost_hist.y[i]);

                Eigen::Vector3d r_a = y_a.segment<3>(0);
                Eigen::Vector3d v_a = y_a.segment<3>(3);

                Eigen::Vector3d r_b = y_b.segment<3>(0);
                Eigen::Vector3d v_b = y_b.segment<3>(3);

                double pos_err = (r_a - r_b).norm();
                double vel_err = (v_a - v_b).norm();

                max_pos_err = std::max(max_pos_err, pos_err);
                max_vel_err = std::max(max_vel_err, vel_err);
            }

            std::cout << "Comparison: " << label << "\n";
            std::cout << "  Points compared : " << n << "\n";
            std::cout << "  Max |dt|        : " << max_time_diff << " s\n";
            std::cout << "  Max |dr|        : " << max_pos_err << " km\n";
            std::cout << "  Max |dv|        : " << max_vel_err << " km/s\n\n";

            return (std::abs(max_time_diff) <= tolerance) && (std::abs(max_pos_err) <= tolerance) && (std::abs(max_vel_err) <= tolerance);
        };

    bool kep_success = compare_histories(hist_kep_boost, hist_kep_astro, 1e-8, "Kepler-only");
    bool j2_success = compare_histories(hist_kep_j2_boost, hist_kep_j2_astro, 1e-8, "Kepler + J2");

    std::cout << "\nKeplerian propagation success flag: " << kep_success;
    std::cout << "\nJ2-perturbed propagation success flag: " << j2_success << "\n\n";

    return 0;
}
