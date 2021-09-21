#pragma once

#define PI 3.141
#define e 2.71828
#define G 9.81

const double atmo_density(const double h);
const double drag(const double Cd, const double v, double const h, const double A);
const double fToAcc(const double m, const double F);
