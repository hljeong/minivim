#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <string>
#include <ncurses.h>
#include "cursor.h"

class Console {
  int h, w;
  Cursor cursor;

public: 
  Console(int r = 0, int c = 0);

  ~Console();

  Cursor& get_cursor_ref() {
    return cursor;
  }

  int get_char() {
    return getch();
  }

  void render(std::vector<std::string> &buffer);
};

#endif
