#include "console.h"
#include <ncurses.h>

Console::Console(int r, int c) : cursor(r, c) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, h, w);
}

Console::~Console() {
  endwin();
}

// todo: proper window
// todo: proper cursor pos
void Console::render(std::vector<std::string> &buffer) {
  clear();

  for (int i = 0, n = buffer.size(); i < n; ++i) {
    mvprintw(i, 0, buffer[i].c_str());
  }

  move(cursor.get_r(), cursor.get_c());
  refresh();
}
