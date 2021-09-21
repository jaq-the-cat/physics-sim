#include <math.h>
#include "physics.h"

const double atmo_density(const double h) {
  // https://www.grc.nasa.gov/www/k-12/airplane/atmosmet.html
  double T, p;
  if (h < 11000) {
    T = 15.04 - .00649*h; 
    p = 101.29 * pow((T + 273.1) / 288.08, 5.256);
  } else if (h < 25000) {
    T = -56.46;
    p = 22.65 * pow(e, 1.73 - .000157*h);
  } else {
    T = -131.21 + .00299*h;
    p = 2.488 * pow((T + 273.1) / 216.6, -11.388);
  }
  return p / (.2869 * (T+273.1));
}

const double drag(const double Cd, const double v, double const h, const double A) {
  return Cd * atmo_density(h) * (v*v/2) * A;
}

const double accToF(const double m, const double a) {
  return m*a;
}

const double fToAcc(const double m, const double F) {
  return F/m;
}
