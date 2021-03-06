#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#include "craft.h"
#include "physics.h"

void print() {
  clear();
  printw("  t-d A:      %f m²\n", rocket.tdArea);
  printw("  l-r A:      %f m²\n", rocket.lrArea);
  printw("  mass:       %f kg\n", rocket.m);
  printw("  thrust:     %f kN\n", rocket.thrust);
  printw("  v_wingArea: %f m²\n", rocket.v_wingArea);
  printw("  h_wingArea: %f m²\n", rocket.h_wingArea);
  printw("  v_Cd:       %f\n", rocket.v_Cd);
  printw("  h_Cd:       %f\n", rocket.h_Cd);
  printw("  Cl_15:      %f\n", rocket.Cl_15);
  printw("  Cl_90:      %f\n", rocket.Cl_90);
  printw("  Fg:         %f kN\n", grav(&rocket)/1000);
  printw("\n");
  printw("  x:          %f km\n", rocket.x);
  printw("  y:          %f km\n", rocket.y);
  printw("  v_velocity: %f m/s\n", rocket.v_velocity);
  printw("  h_velocity: %f m/s\n", rocket.h_velocity);
  printw("\n");
  printw("  angle:      %f°\n", rocket.angle);
  printw("  vThrust:    %f kN\n", vThrust(&rocket)/1000.);
  printw("  hThrust:    %f kN\n", hThrust(&rocket)/1000.);
  printw("  vLift:      %f N\n", vLift(&rocket));
  printw("  hLift:      %f N\n", hLift(&rocket));
  printw("  vDrag:      %f kN\n", vDrag(&rocket)/1000);
  printw("  hDrag:      %f kN\n", hDrag(&rocket)/1000);
  printw("\n");
  printw("  vCl:        %f\n", vCl(&rocket));
  printw("  hCl:        %f\n", hCl(&rocket));
  printw("  atmo:       %f\n", atmo_density(rocket.y));
  printw("  vArea:      %f\n", vArea(&rocket));
  printw("  hArea:      %f\n", hArea(&rocket));
}

void update() {
  double vdrag = -vDrag(&rocket);
  double hdrag = -hDrag(&rocket);
  if (rocket.v_velocity < 0)
    vdrag *= -1;
  if (rocket.h_velocity < 0)
    hdrag *= -1;

  double vacc = fToAcc(rocket.m,
    vThrust(&rocket)
    + vdrag
    - grav(&rocket)
  );

  double hacc = fToAcc(rocket.m,
    hThrust(&rocket)
    + hdrag
    + hLift(&rocket)
  );
  printw("vacc: %f\n", vacc);
  printw("hacc: %f\n", hacc);
  rocket.v_velocity += vacc;
  rocket.h_velocity += hacc;
  /*rocket.y += rocket.v_velocity;*/
  /*rocket.x += rocket.h_velocity;*/
}

int main(int argc, char* argv[]) {
  initscr();
  noecho();
  timeout(0);
  curs_set(FALSE);
  while (1) {
    print();
    update();
    refresh();

    int ch = getch();
    switch (ch) {
      case 'q':
        goto end;
      case 'a':
        left(&rocket);
        break;
      case 'd':
        right(&rocket);
        break;
    }
    napms(300);
  }
  end:
  endwin();
}
