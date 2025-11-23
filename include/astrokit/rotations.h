#pragma once

#include <cmath>
#include <Eigen/Dense>

namespace astrokit
{
	//note: all angles in this script assume radians

	inline constexpr Eigen::Vector3d i_hat(1, 0, 0);
	inline constexpr Eigen::Vector3d j_hat(0, 1, 0);
	inline constexpr Eigen::Vector3d k_hat(0, 0, 1);

	inline Eigen::Matrix3d abritrary_axis_rotation(double angle, Eigen::Vector3d axis)
	{
		return Eigen::Matrix3d(1, 0, 0, 0, 1, 0, 0, 0, 1); //will fill this in later; not currently using it
	}

	inline Eigen::Matrix3d x_rotation(double angle)
	{
		Eigen::Matrix3d C;
		double ca = std::cos(angle);
		double sa = std::sin(angle);

		C << 1,  0,   0,
     		 0, ca, -sa,
			 0, sa,  ca;

		return C;
	}

	inline Eigen::Matrix3d y_rotation(double angle)
	{
		Eigen::Matrix3d C;
		double ca = std::cos(angle);
		double sa = std::sin(angle);
	
		C << ca, 0, sa,
			  0, 1,  0,
			-sa, 0, ca;

		return C;
	}

	inline Eigen::Matrix3d z_rotation(double angle)
	{
		Eigen::Matrix3d C;
		double ca = std::cos(angle);
		double sa = std::sin(angle);

		C << ca, -sa, 0,
			 sa,  ca, 0,
			  0,   0, 1;

		return C;
	}

	inline Eigen::Matrix3d lonlat_to_cart(double lon, double lat)
	{
		//lon = rotation about z
		Eigen::Matrix3d C1 = ZRotation(lon);

		//lat = rotaiton about y
		Eigen::Matrix3d C2 = YRotation(lat);

		Eigen::Matrix3d C = C1 * C2;

		return C;
	}

} // namespace astrokit

