#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#include "craft.h"
#include "physics.h"

void print() {
  clear();
  printw("STATS:\n");
  printw("  height:     %f\n", delta2.height);
  printw("  thrust:     %f\n", delta2.thrust);
  printw("  v_Cd:       %f\n", delta2.v_Cd);
  printw("  h_Cd:       %f\n", delta2.h_Cd);
  printw("  Fg:         %f\n", delta2.m*G);
  printw("\n");
  printw("DATA:\n");
  printw("  x:          %f\n", delta2.x);
  printw("  y:          %f\n", delta2.y);
  printw("  angle:      %f\n", delta2.angle);
  printw("  v_velocity: %f\n", delta2.v_velocity);
  printw("  h_velocity: %f\n", delta2.h_velocity);
  printw("\n");
  printw("  vDrag:      %f\n", vDrag());
  printw("  hDrag:      %f\n", hDrag());
  printw("  vThrust:    %f\n", vThrust());
  printw("  hThrust:    %f\n", hThrust());
  printw("\n");
  printw("thing: %f\n", 2.488 * pow((-131.21 + .00299*0 + 273.1)/216.6, -11.388));
  printw("atmo:  %f\n", atmo_density(0));
}

void update() {
  delta2.v_velocity += fToAcc(delta2.m,
    vThrust() - vDrag() - delta2.m*G);
  delta2.h_velocity += fToAcc(delta2.m,
      hThrust() - hDrag());
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
        left();
        break;
      case 'd':
        right();
        break;
    }
    napms(300);
  }
  end:
  endwin();
}
