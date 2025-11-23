#pragma once

#include <cmath>
#include <Eigen/Dense>
#include "math_utils.h"
#include "rotations.h"

namespace astrokit
{
    inline Eigen::Vector<double, 6> cart_to_coe(Eigen::Vector<double, 6> cart, double mu)
    // return order: sma, ecc, inc, raan, argp, ta
    {
        r = cart.segment<3>(0);
        v = cart.segment<3>(3);

        double R = r.norm();
        double V = v.norm();

        // sma - use the orbital specific energy
        double eps = V * V / 2 - mu / R;
        double sma = -mu / (2 * eps);

        // ecc - directly compute ecc vector
        Eigen::Vector3d h = r.cross(v);
        Eigen::Vector3d e_vec = v.cross(h) / mu - r / R;
        double ecc = e_vec.norm();

        // inc - from angular momentum vector
        Eigen::Vector3d h_hat = h.normalized();
        double inc = safe_acos(h_hat[2]);

        // raan - compute ascending node vector
        Eigen::Vector3d n = k_hat.cross(h_hat); //k_hat from rotations.h
        double raan = std::atan2(n[1], n[0]);

        // argp - use node & ecc vectors
        double argp = safe_acos(e_vec.dot(n) / (ecc * n.norm()));
        if (e_vec[2] < 0.0)
        {
            argp = 2 * PI - argp;
        }

        // ta - use position & eccentricity vectors
        double ta = std::atan2(std::sqrt(1 - ecc * ecc) * r.dot(h), r.dot(e_vec));

        Eigen::Vector<double, 6> coes;
        coes << sma, ecc, inc, raan, argp, ta;

        return coes;

    }

    inline Eigen::Vector<double, 6> coe_to_cart(Eigen::Vector<double, 6> coes, double mu)
    {
        double a = coes[0];
        double e = coes[1];
        double i = coes[2];
        double Om = coes[3];
        double w = coes[4];
        double f = coes[5];

        //start with perifocal coords
        double p = a * (1 - e * e);
        double r = p / (1 + e * std::cos(f));
        Eigen::Vector3d r_pf(r * std::cos(f), r * std::sin(f), 0);
        Eigen::Vector3d v_pf(-std::sin(f), e + std::cos(f), 0);
        v_pf *= std::sqrt(mu / p);

        //and construct the 3-1-3 rotation matrix
        double cOm = std::cos(Om);
        double sOm = std::sin(Om);
        double cw = std::cos(w);
        double sw = std::sin(w);
        double ci = std::cos(i);
        double si = std::sin(i);

        Eigen::Matrix3d C;
        C << cOm * cw - sOm * sw * ci, -cOm * sw - sOm * cw * ci, sOm* si,
             sOm* cw + cOm * sw * ci, -sOm * sw + cOm * cw * ci, -cOm * si,
             sw* si, cw* si, ci;

        Eigen::Vector3d r_cart = C * r_pf;
        Eigen::Vector3d v_cart = C * v_pf;

        Eigen::Vector<double, 6> cart;
        cart << r_cart, v_cart;

        return cart;
    }
}// namespace astrokit