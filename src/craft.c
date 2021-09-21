#include "craft.h"
#include "physics.h"
#include <math.h>

#define P(x, y) (point) {x, y}
#define F(fa, x) fa.m*x - fa.a1 + fa.a2

#define CF(at0, at90) F(ffp(P(0, at0), P(90, at90)), craft->angle)

Craft delta2 = {
  .height = 38.9,
  .length = 2.44,
  .m = 4470,
  .thrust = 970,
  .v_Cd = 0.35,
  .h_Cd = 1.1,
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

double vCd(Craft *craft) { // nose-engine
  return CF(craft->v_Cd, craft->h_Cd);
  /*return 0.0083333 * craft->angle + 0.35;*/
}

double hCd(Craft *craft) { // left-right
  return CF(craft->h_Cd, craft->v_Cd);
  /*return -0.0083333 * craft->angle + 1.1;*/
}

double vThrust(Craft *craft) {
  return CF(craft->thrust, 0) * 1000; // kN to N
  /*return (-10.77778 * craft->angle + 970) * 1000; // kN to N*/
}

double hThrust(Craft *craft) {
  return CF(0, craft->thrust) * 1000; // kn to N
  /*return (10.77778 * craft->angle) * 1000; // kN to N*/
}

double vArea(Craft *craft) { // nose-engine
  return CF(craft->length, craft->height);
  /*return 0.4051111 * craft->angle + 2.44;*/
}

double hArea(Craft *craft) { // left-right
  return CF(craft->height, craft->length);
  /*return -0.4051111 * craft->angle + 38.9;*/
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
