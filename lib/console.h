#ifndef CONSOLE_H
#define CONSOLE_H

#include <ncurses.h>
#include "buffer.h"

#define TAB_SIZE 2

class Console {
  int height;
  int width;
  int viewport_line;
  int viewport_pos;

public: 
  Console();

  ~Console();

  int get_char() {
    return getch();
  }

  int move_viewport_to_cursor(const Buffer& buffer);

  int render(const Buffer& buffer);
};

#endif
