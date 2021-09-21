#pragma once

typedef struct {
  const double height; // m
  const double d;
  const double m; // kg
  const double thrust; // kN
  const double v_Cd;
  const double h_Cd;

  double x, y; // m

  double angle; // degrees

  double v_velocity; // m/s
  double h_velocity;
} Craft;

extern Craft delta2;

double vDrag(Craft*);
double hDrag(Craft*);
double vThrust(Craft*);
double hThrust(Craft*);
void left(Craft*);
void right(Craft*);
