#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#include "craft.h"
#include "physics.h"

void print() {
  clear();
  printw("STATS:\n");
  printw("  height:     %f m\n", delta2.height);
  printw("  diameter:   %f m\n", delta2.d);
  printw("  thrust:     %f kN\n", delta2.thrust);
  printw("  v_Cd:       %f\n", delta2.v_Cd);
  printw("  h_Cd:       %f\n", delta2.h_Cd);
  printw("  Fg:         %f N\n", delta2.m*G);
  printw("\n");
  printw("DATA:\n");
  printw("  x:          %f km\n", delta2.x);
  printw("  y:          %f km\n", delta2.y);
  printw("  angle:      %f deg\n", delta2.angle);
  printw("  v_velocity: %f m/s\n", delta2.v_velocity);
  printw("  h_velocity: %f m/s\n", delta2.h_velocity);
  printw("\n");
  printw("  vDrag:      %f N\n", vDrag(&delta2));
  printw("  hDrag:      %f N\n", hDrag(&delta2));
  printw("  vThrust:    %f N\n", vThrust(&delta2));
  printw("  hThrust:    %f N\n", hThrust(&delta2));
  printw("\n");
  printw("atmo:  %f\n", atmo_density(delta2.y));
}

void update() {
  delta2.v_velocity += fToAcc(delta2.m,
    vThrust(&delta2) - vDrag(&delta2) - delta2.m*G);
  delta2.h_velocity += fToAcc(delta2.m,
      hThrust(&delta2) - hDrag(&delta2));
  /*delta2.y += delta2.v_velocity;*/
  /*delta2.x += delta2.h_velocity;*/
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
        left(&delta2);
        break;
      case 'd':
        right(&delta2);
        break;
    }
    napms(300);
  }
  end:
  endwin();
}
