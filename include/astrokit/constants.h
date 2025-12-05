#pragma once

#include <numbers>
#include "unit_structs.h"

// this file last generated on 2025-10-11 16:43
// data pulled from C:/astrokit/data/planet_database.json

namespace astrokit 
{
    constexpr Mu MU_SUN{ 132712000000.0 };
    constexpr Distance AU{ 149598000.0 };
    constexpr double PI            = std::numbers::pi;
    constexpr double DEG2RAD       = PI / 180.0;
	constexpr double RAD2DEG       = 180.0 / PI;
    constexpr double SEC2DAY       = 86400.0;
    constexpr double SEC2YEAR      = 86400.0 * 365.25;
    constexpr double DAY2SEC       = 1.0 / SEC2DAY;
    constexpr double YEAR2SEC      = 1.0 / SEC2YEAR;

    //note: want to set up our structs to include multiple unit options. instead
    //      of planet.SMA_km (to make sure the unit information is clear), you 
    //      can say planet.SMA and it will default to km, but you can also say
    //      planet.SMA.km, planet.SMA.m, or planet.SMA.au to specify the units.
    //      this is all handled in unit_structs.h

    struct Planet {
        //Mu, Distance, Angle, & Time are custom structs from unit_structs.h
        Mu MU;
        Distance R_MEAN;
        Distance R_EQUATOR;
        Distance R_POLE;
        Distance SMA;
        Angle ECC;
        Angle INC;
        Time T;
        Time T_SYNODIC;
        double J2;
    };

    // Following planetary parameters from the GSFC Planetary Fact Sheets
    inline constexpr Planet MERCURY =
    {
        .MU{22032.0},
        .R_MEAN{2439.7},
        .R_EQUATOR{2440.5},
        .R_POLE{2438.3},
        .SMA{57909000.0},
        .ECC{0.2056},
        .INC{7.004},
        .T{87.9691 * DAY2SEC},
        .T_SYNODIC{115.88 * DAY2SEC},
        .J2{5.03e-5}
    };

    inline constexpr Planet VENUS =
    {
        .MU{324860.0},
        .R_MEAN{6051.8},
        .R_EQUATOR{6051.8},
        .R_POLE{6051.8},
        .SMA{108210000.0},
        .ECC{0.0068},
        .INC{3.395},
        .T{224.701 * DAY2SEC},
        .T_SYNODIC{583.92 * DAY2SEC},
        .J2{4.458e-6}
    };                

    inline constexpr Planet EARTH =
    {
        .MU{398600.4418},
        .R_MEAN{6371.0},
        .R_EQUATOR{6378.1},
        .R_POLE{6356.8},
        .SMA{149598000.0},
        .ECC{0.0167},
        .INC{0.0},
        .T{365.256 * DAY2SEC},
        .T_SYNODIC{0.0},
        .J2{1.08263e-3}
    };
    
    inline constexpr Planet MARS =
    {
        .MU{42828.0},
        .R_MEAN{3389.5},
        .R_EQUATOR{3396.2},
        .R_POLE{3376.2},
        .SMA{227956000.0},
        .ECC{0.0935},
        .INC{1.848},
        .T{686.98 * DAY2SEC},
        .T_SYNODIC{779.94 * DAY2SEC},
        .J2{1.96045e-3}
    };
    
    inline constexpr Planet JUPITER =
    {
        .MU{126687000.0},
        .R_MEAN{69911.0},
        .R_EQUATOR{71492.0},
        .R_POLE{66854.0},
        .SMA{778479000.0},
        .ECC{0.0487},
        .INC{1.304},
        .T{4332.589 * DAY2SEC},
        .T_SYNODIC{398.88 * DAY2SEC},
        .J2{0.014736}
    };
    
    inline constexpr Planet SATURN =
    {
        .MU{37931000.0},
        .R_MEAN{58232.0},
        .R_EQUATOR{60268.0},
        .R_POLE{54364.0},
        .SMA{1432041000.0},
        .ECC{0.052},
        .INC{2.486},
        .T{10755.699 * DAY2SEC},
        .T_SYNODIC{378.09 * DAY2SEC},
        .J2{0.016298}
    };
    
    inline constexpr Planet URANUS =
    {
        .MU{5794000.0},
        .R_MEAN{25362.0},
        .R_EQUATOR{25559.0},
        .R_POLE{24973.0},
        .SMA{2867043000.0},
        .ECC{0.0469},
        .INC{0.77},
        .T{30685.4 * DAY2SEC},
        .T_SYNODIC{369.66 * DAY2SEC},
        .J2{0.00334343}
    };
    
    inline constexpr Planet NEPTUNE =
    {
        .MU{6835100.0},
        .R_MEAN{24622.0},
        .R_EQUATOR{24764.0},
        .R_POLE{24341.0},
        .SMA{4514953000.0},
        .ECC{0.0097},
        .INC{1.77},
        .T{60189.018 * DAY2SEC},
        .T_SYNODIC{367.49 * DAY2SEC},
        .J2{0.003411}
    };
} // namespace astrokit