#pragma once

#include <numbers>

//trying for a light-weight version of a Unit system (inspired by Monte)
    //note: the immediate use for this is a type-safe framework for making the constants.h Planet struct more robust
    //		but there will likely be broader use cases for this generic system down the road. if there aren't it was 
    //		still fun to poke at

namespace astrokit 
{
#pragma region quantity defs
    //first we need a generic struct to define what a generic quantity's units are  (just looking at length & time for now)
    template<int L, int T> //length, time (powers of; e.g. L = 3, T = -2 -> Length^3/Time^2 [mu])
    struct Quantity
    {
        double value;

        constexpr explicit Quantity(double v) : value(v) {}

        constexpr operator double() const
        {
            return value;
        }
    };

    //now that we know what a generic quantity is, need to define the primary mathematical operators
    // (just defining +, -, *, / for now)
    template<int L, int T>
    constexpr Quantity<L, T> operator+(Quantity<L, T> q1, Quantity<L, T> q2)
    {
        return Quantity<L, T>{q1.value + q2.value};
    }

    template<int L, int T>
    constexpr Quantity<L, T> operator-(Quantity<L, T> q1, Quantity<L, T> q2)
    {
        return Quantity<L, T>{q1.value - q2.value};
    }

    
    template<int L1, int T1, int L2, int T2>
    constexpr Quantity<L1 + L2, T1 + T2> operator*(Quantity<L1, T1> q1, Quantity<L2, T2> q2)
    {
        return Quantity<L1 + L2, T1 + T2>{q1.value* q2.value};
    }

    template<int L1, int T1, int L2, int T2>
    constexpr Quantity<L1 - L2, T1 - T2> operator/(Quantity<L1, T1> q1, Quantity<L2, T2> q2)
    {
        return Quantity<L1 - L2, T1 - T2>{q1.value / q2.value};
    }
#pragma endregion quantity defs

#pragma region unit defs
    //now to define our core quantities/units
    struct Distance : Quantity<1, 0> //length^1, time^0
    {
        double km;
        double m;
        double au;

        //use a constructor to create each distance unit
        constexpr explicit Distance(double value_km) :
            Quantity<1, 0>(value_km), km(value_km), m(value_km * 1000.0), au(value_km / 149598000.0) {}

        //use a double operator to define the default unit
        constexpr operator double() const
        {
            return km;
        }//this makes the behavior s.t. planet.SMA is in km but planet.SMA.km, planet.SMA.m, or planet.SMA.au are also options
    };

    //need the same for angles
    struct Angle //note: not using the Quantity struct here; that will treat angles the same as any other unitless number.
        //      that's not the desired behavior here but I don't have the time to complicate the unit handling
        //      right now and it will not impact the usage for Angles.
    {
        double deg;
        double rad;

        constexpr explicit Angle(double value_deg) : deg(value_deg), rad(value_deg* std::numbers::pi / 180.0) {}

        constexpr operator double() const
        {
            return rad; //note: takes an angle in degrees in the constructor and defaults to radians in the output.
                        //      don't like switching units like this but this is almost always how I end up using angles.
                        //      the planetary constants are also provided in degrees which is currently the primary/only 
                        //      use for this struct
        }
    };

    //and time
    struct Time : Quantity<0, 1> //length^0, time^1
    {
        double sec;
        double min;
        double hr;
        double day;
        double yr;

        constexpr explicit Time(double value_s) :
            Quantity<0, 1>(value_s), sec(value_s), min(value_s / 60.0), hr(value_s / 3600.0), day(value_s / 86400.0), yr(value_s / (86400.0 * 365.25)) {}

        constexpr operator double() const
        {
            return sec;
        }
    };

    //can make one for MU as well
    struct Mu : Quantity<3, -2>
    {
        double km3_s2;
        double m3_s2;

        constexpr explicit Mu(double value_km3_s2) :
            Quantity<3, -2>(value_km3_s2), km3_s2(value_km3_s2), m3_s2(value_km3_s2 * 1.0e9) {}

        constexpr Mu(Quantity<1, 0> L, Quantity<0, 1> T) :
            Mu((L.value* L.value* L.value) / (T.value * T.value)) {
        }

        constexpr operator double() const
        {
            return km3_s2;
        }
    };
#pragma endregion unit defs
} //namespace astrokit