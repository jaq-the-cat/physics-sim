#pragma once

typedef struct {
  // static data
  const double tdArea;     // m²
  const double lrArea;     // m²
  const double m;          // kg
  const double thrust;     // kN
  const double v_wingArea; // m²
  const double h_wingArea; // m²

  const double v_Cd;
  const double h_Cd;
  const double Cl_15;
  const double Cl_90;

  // dynamic data
  double angle;            // degrees

  double x, y;             // m

  double v_velocity;       // m/s
  double h_velocity;       // m/s
} Craft;

extern Craft rocket;

double vDrag(Craft*);
double hDrag(Craft*);
double vCl(Craft*);
double hCl(Craft*);
double vThrust(Craft*);
double hThrust(Craft*);
double vLift(Craft*);
double hLift(Craft*);
void left(Craft*);
void right(Craft*);
