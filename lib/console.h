#ifndef CONSOLE_H
#define CONSOLE_H

#include <ncurses.h>
#include <string>
#include "buffer.h"

#define TAB_SIZE 2

#include <bits/stdc++.h>

class Console {
  int window_height;
  int window_width;
  int viewport_line;
  int viewport_pos;
  int viewport_height;
  int viewport_width;
  int line_num_width;

public: 
  Console(const Buffer& buffer);

  ~Console();

  int get_char() {
    return getch();
  }

  int move_viewport_to_cursor(const Buffer& buffer);

  int clear_screen() {
    return clear();
  }

  int render_status(const std::string& mode);

  int render_buffer(const Buffer& buffer);

  int render_to_screen() {
    return refresh();
  }
};

#endif
