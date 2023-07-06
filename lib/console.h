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

  int validate_viewport();

  int render(const Buffer &buffer);

  int backspace(int signal);

  int linefeed();

  int insert_char();

  int cursor_up(int signal);

  int cursor_down(int signal);

  int cursor_left(int signal);

  int cursor_right(int signal);
};

#endif
