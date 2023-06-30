// #include<stdlib.h>
// #include <ncurses.h>
#include "minivim.h"

int main() {
  Minivim minivim;
  return minivim.run();

  /*
  int h, w;
  int ch;
  int y = 0, x = 0;

  initscr();
  // cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, h, w);

  while (1) {
    if (ch == KEY_F(4)) {
      endwin();
      exit(0);
    }
    
    ch = getch();
    mvprintw(y, x, "%c", ch);
    if (++x == w) {
      ++y;
      x = 0;
    }
    refresh();
  }

  endwin();
  return 0;
  */
}
