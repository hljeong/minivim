#ifndef CONSOLE_H
#define CONSOLE_H

#include <ncurses.h>
#include "buffer.h"

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

  int validate_viewport();

  int render(const Buffer &buffer);

  int backspace(int signal);

  int linefeed();

  int insert_char();
};

#endif
