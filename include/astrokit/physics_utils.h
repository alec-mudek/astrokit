#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <array>
#include <stdexcept>

#include "constants.h"
#include "math_utils.h"

namespace astrokit
{
	inline double exp_atmo(double alt, double rho0, double scale_height)
	{
		double rho = rho0 * exp(-alt / scale_height);

		return rho;
	}

	inline double exp_atmo(double alt_km, const Planet& body)
	//use the scale height & ref density from constants.y
	{
		return exp_atmo(alt_km, body.SURFACE_DENSITY, body.SCALE_HEIGHT);
	}

	inline std::array<double, 3> time_past_reference_epoch(double jd, double ref_epoch = 2451545.0)
	//returns the time past reference epoch in 3 forms: seconds, centuries, & days
	{
		double d = jd - ref_epoch;
		double dt = d * DAY2SEC;
		double T = d / 36525;
		
		return std::array<double, 3>(dt, T, d);
	}

	inline std::array<double, 3> mercury_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double M1 = 174.7910857 + 4.092335 * d;
		double M2 = 349.5821714 + 8.18467 * d;
		double M3 = 164.3732571 + 12.277005 * d;
		double M4 = 339.1643429 + 16.36934 * d;
		double M5 = 153.9554286 + 20.461675 * d;

		double M1_term =  0.01067257 * sind(M1);
		double M2_term = -0.00112309 * sind(M2);
		double M3_term = -0.00011040 * sind(M3);
		double M4_term = -0.00002539 * sind(M4);
		double M5_term = -0.00000571 * sind(M5);

		double alpha0 = 281.0103 + -0.0328 * T;
		double delta0 = 61.4155 + -0.0049 * T;
		double W = 329.5988 + 6.1385108 * d + M1_term + M2_term + M3_term + M4_term + M5_term;

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
		// note: values returned in rad instead of deg
	}

	inline std::array<double, 3> venus_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
	
		double alpha0 = 272.76;
		double delta0 = 67.16;
		double W = 160.2 - 1.4813688 * dts[2];

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
		// note: values returned in rad instead of deg
	}

	inline std::array<double, 3> earth_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2009 (removed in 2015 due to low accuracy; good enough for rough analysis work)
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double alpha0 = -0.641 * T;
		double delta0 = 90.0 - 0.557 * T;
		double W = 190.147 + 360.9856235 * d;

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
		// note: values returned in rad instead of deg
	}

	inline std::array<double, 3> mars_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double a0t1 = 0.000068 * sind(198.991226 + 19139.4819985 * T);
		double a0t2 = 0.000238 * sind(226.292679 + 38280.8511281 * T);
		double a0t3 = 0.000052 * sind(249.663391 + 57420.7251593 * T);
		double a0t4 = 0.000009 * sind(266.183510 + 76560.6367950 * T);
		double a0t5 = 0.419057 * sind(79.398797 + 0.5042615 * T);

		double alpha0 = 317.269202 - 0.10927547 * T + a0t1 + a0t2 + a0t3 + a0t4 + a0t5;

		double d0t1 = 0.000051 * cosd(122.433576 + 19139.9407476 * T);
		double d0t2 = 0.000141 * cosd(43.058401 + 38280.8753272 * T);
		double d0t3 = 0.000031 * cosd(57.663379 + 57420.7517205 * T);
		double d0t4 = 0.000005 * cosd(79.476401 + 76560.6495004 * T);
		double d0t5 = 1.591274 * cosd(166.325722 + 0.5042615 * T);

		double delta0 = 54.432516 - 0.05827105 * T + d0t1 + d0t2 + d0t3 + d0t4 + d0t5;

		double Wt1 = 0.000145 * sind(129.071773 + 19140.0328244 * T);
		double Wt2 = 0.000157 * sind(36.352167 + 38281.0473591 * T);
		double Wt3 = 0.000040 * sind(56.668646 + 57420.9295360 * T);
		double Wt4 = 0.000001 * sind(67.364003 + 76560.2552215 * T);
		double Wt5 = 0.000001 * sind(104.792680 + 95700.4387578 * T);
		double Wt6 = 0.584542 * sind(95.391654 + 0.5042615 * T);

		double W = 176.049863 + 350.891982443297 * d + Wt1 + Wt2 + Wt3 + Wt4 + Wt5 + Wt6;

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
	}

	inline std::array<double, 3> jupiter_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double Ja = 99.360714 + 4850.4046 * T;
		double Jb = 175.895369 + 1191.9605 * T;
		double Jc = 300.323162 + 262.5475 * T;
		double Jd = 114.012305 + 6070.2476 * T;
		double Je = 49.511251 + 64.3000 * T;

		double alpha0 = 268.056595 - 0.006499 * T + 
						0.000117 * sind(Ja) + 0.000938 * sind(Jb) + 0.001432 * sind(Jc) + 
						0.000030 * sind(Jd) + 0.002150 * sind(Je);

		double delta0 = 64.495303 + 0.002413 * T +
						0.000050 * cosd(Ja) + 0.000404 * cosd(Jb) + 0.000617 * cosd(Jc) -
						0.000013 * cosd(Jd) + 0.000926 * cosd(Je);

		double W = 284.95 + 870.5360000 * d;

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
	}

	inline std::array<double, 3> saturn_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double alpha0 = 40.589 - 0.036 * T;
		double delta0 = 83.537 - 0.004 * T;
		double W = 38.90 + 810.7939024 * d;

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
	}

	inline std::array<double, 3> uranus_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);

		double alpha0 = 257.311;
		double delta0 = -15.175;
		double W = 203.81 - 501.1600928 * dts[2];

		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
	}

	inline std::array<double, 3> neptune_ref_angles(double jd)
	//from IAU Cartogrphic Coords 2015
	{
		std::array<double, 3> dts = time_past_reference_epoch(jd);
		double T = dts[1];
		double d = dts[2];

		double N = 357.85 + 52.316 * T;

		double alpha0 = 299.36 + 0.70 * sind(N);
		double delta0 = 43.46 - 0.51 * cosd(N);
		double W = 249.978 + 541.1397757 * d - 0.48 * sind(N);
			
		return std::array<double, 3>(alpha0 * DEG2RAD, delta0 * DEG2RAD, W * DEG2RAD);
	}

	inline std::array<double, 3> body_ref_angles(double jd, Planet& body)
	//function to compute the alpha, delta, & W from the IAU Cartographic Coords Report (2015)
	{
		// note: CURRENTLY ASSUMES IDS 0-7 ARE RESERVED FOR THE PLANETS.
		//		 if you try to pass in any other number it will currently fail.
		//		 if you give it an index in the range [0, 7] that you do not 
		//		 intend to be the corresponding planet, you will not get the data you expect out.
		switch (body.ID)
		{
			case PlanetEnum::MERCURY: return mercury_ref_angles(jd);
			case PlanetEnum::VENUS: return venus_ref_angles(jd);
			case PlanetEnum::EARTH: return earth_ref_angles(jd);
			case PlanetEnum::MARS: return mars_ref_angles(jd);
			case PlanetEnum::JUPITER: return jupiter_ref_angles(jd);
			case PlanetEnum::SATURN: return saturn_ref_angles(jd);
			case PlanetEnum::URANUS: return uranus_ref_angles(jd);
			case PlanetEnum::NEPTUNE: return neptune_ref_angles(jd);
			default: throw std::runtime_error("BodyError: body_ref_angles doesn't support the input body.");
		}
	}
} // namespace astrokit