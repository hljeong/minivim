#include <iostream>
#include <ncurses.h>
using namespace std;

int main() {
  initscr();
  printw("hello");
  refresh();
  getch();
  endwin();

  return 0;
}
