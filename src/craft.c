#include "craft.h"
#include "physics.h"
#include <math.h>

#define P(x, y) (point) {x, y}
#define F(fa, x) (fa.m*x - fa.a1 + fa.a2)

#define CF(deg1, atdeg1, deg2, atdeg2) (F(ffp(P(deg1, atdeg1), P(deg2, atdeg2)), craft->angle))

Craft delta2 = {
  // static data
  .tdArea = 2.44*PI,   // m²
  .lrArea = 38.9*2.44, // m²
  .m = 4470,           // kg
  .thrust = 970,       // kN
  .v_wingArea = 0,  // m²
  .h_wingArea = 2.5,  // m²

  .v_Cd = .35,         // drag coeff at 0deg
  .h_Cd = 1.1,         // drag coeff at 90deg
  .Cl_15 = .4,         // lift coefficient at 15deg
  .Cl_90 = -.1,        // lift coefficient at 90deg

  // dynamic data
  .angle = 0,          // vertical
};

typedef struct {
  double x, y;
} point;

typedef struct {
  const double m, a1, a2;
} funcArgs;

funcArgs ffp(point p1, point p2) {
  const double m = fabs(p2.y-p1.y)/fabs(p2.x-p1.x);
  // y - (p1.y) = m * (x - p1.x)
  // y = m * (x - p1.x) + (p1.y)
  // y = m*x - m*p1.x + p1.y
  return (funcArgs) {
    .m = m,
    .a1 = m*p1.x,
    .a2 = p1.y
  };
}

// Equation oncstants
double vCd(Craft *craft) { // top-down
  return CF(0, craft->v_Cd, 90, craft->h_Cd);
}

double hCd(Craft *craft) { // right-left
  return CF(0, craft->h_Cd, 90, craft->v_Cd);
}

double vCl(Craft *craft) { // top-down
  if (craft->angle < 15)
    return CF(0, 0, 15, craft->Cl_15);
  return CF(15, craft->Cl_15, 90, craft->Cl_90);
}

double hCl(Craft *craft) { // right-left
  if (craft->angle < 75)
    return CF(0, craft->Cl_90, 75, craft->Cl_15);
  return CF(75, craft->Cl_15, 90, 0);
}

// Sizes
double vArea(Craft *craft) { // top-down
  return CF(0, craft->tdArea, 90, craft->lrArea);
}

double hArea(Craft *craft) { // right-left
  return CF(0, craft->lrArea, 90, craft->tdArea);
}

double vWingArea(Craft *craft) { // top-down
  return CF(0, craft->v_wingArea, 90, craft->h_wingArea);
}

double hWingArea(Craft *craft) { // right-left
  return CF(0, craft->h_wingArea, 90, craft->v_wingArea);
}

// Forces
double vThrust(Craft *craft) {
  return CF(0, craft->thrust, 90, 0) * 1000; // kN to N
}

double hThrust(Craft *craft) {
  return CF(0, 0, 90, craft->thrust) * 1000; // kn to N
}

double vLift(Craft *craft) {
  return vCl(craft) * (atmo_density(craft->y) * craft->v_velocity*craft->v_velocity)/2 * craft->v_wingArea;
}

double hLift(Craft *craft) {
  return hCl(craft) * (atmo_density(craft->y) * craft->h_velocity*craft->h_velocity)/2 * craft->h_wingArea;
}

double vDrag(Craft *craft) { // vertical drag
  return drag(vCd(craft), craft->v_velocity, craft->y, vArea(craft));
}

double hDrag(Craft *craft) { // horizontal drag
  return drag(hCd(craft), craft->h_velocity, craft->y, hArea(craft));
}

void left(Craft *craft) {
  if (craft->angle > 0)
    craft->angle -= 1.0;
}

void right(Craft *craft) {
  if (craft->angle < 90)
    craft->angle += 1.0;
}
