#include "craft.h"
#include "physics.h"

Craft delta2 = {
  .height = 38.9,
  .d = 2.44,
  .m = 4470,
  .thrust = 970,
  .v_Cd = 0.35,
  .h_Cd = 1.1,
};

double vCd() { // nose-engine
  return 0.0083333 * delta2.angle + 0.35;
}

double hCd() { // left-right
  return -0.0083333 * delta2.angle + 1.1;
}

double vThrust() {
  return (-10.77778 * delta2.angle + 970) * 1000; // kN to N
}

double hThrust() {
  return (10.77778 * delta2.angle) * 1000; // kN to N
}

double vArea() { // nose-engine
  return 0.4051111 * delta2.angle + 2.44;
}

double hArea() { // left-right
  return -0.4051111 * delta2.angle + 38.9;
}

double vDrag() { // vertical drag
  return drag(vCd(), delta2.v_velocity, delta2.y, vArea());
}

double hDrag() { // horizontal drag
  return drag(hCd(), delta2.h_velocity, delta2.y, hArea());
}

void left() {
  if (delta2.angle > 0)
    delta2.angle -= 1.0;
}

void right() {
  if (delta2.angle < 90)
    delta2.angle += 1.0;
}
