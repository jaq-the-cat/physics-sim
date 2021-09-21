#pragma once

#define PI 3.141
#define e 2.71828
#define G 6.674e-11

double atmo_density(double h);
double drag(double Cd, double v, double h, double A);
double fToAcc(double m, double F);
