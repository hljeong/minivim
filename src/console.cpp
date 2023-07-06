#include <ncurses.h>
#include "commands.h"
#include "console.h"

Console::Console() : 
  viewport_line(0), 
  viewport_pos(0) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, height, width);
}

Console::~Console() {
  endwin();
}

int Console::validate_viewport() {
  getmaxyx(stdscr, height, width);

  if (viewport_line < 0) {
    viewport_line = 0;
  } else if (viewport_line >= height) {
    viewport_line = height - 1;
  }

  if (viewport_pos < 0) {
    viewport_pos = 0;
  } else if (viewport_pos >= width) {
    viewport_pos = width - 1;
  }

  return 0;
}

int Console::backspace(int signal) {
  if (signal & BACKSPACE_CROSS_LINE) {
    --viewport_line;

    int delta_pos = signal & BACKSPACE_CROSS_LINE_DELTA_MASK;
    viewport_pos += delta_pos;
  } else if (!(signal & BACKSPACE_DO_NOTHING)) {
    --viewport_pos;
  }

  validate_viewport();

  return 0;
}

int Console::linefeed() {
  ++viewport_line;

  viewport_pos = 0;

  validate_viewport();

  return 0;
}

int Console::insert_char() {
  ++viewport_pos;

  validate_viewport();

  return 0;
}

int Console::cursor_up(int signal) {
  if (!(signal & CURSOR_MOVED)) {
    return 0;
  }

  --viewport_line;

  viewport_pos = signal & CURSOR_POS_MASK;

  validate_viewport();

  return 0;
}

int Console::cursor_down(int signal) {
  if (!(signal & CURSOR_MOVED)) {
    return 0;
  }

  ++viewport_line;

  viewport_pos = signal & CURSOR_POS_MASK;

  validate_viewport();

  return 0;
}

int Console::cursor_left(int signal) {
  if (!(signal & CURSOR_MOVED)) {
    return 0;
  }

  --viewport_pos;

  validate_viewport();

  return 0;
}

int Console::cursor_right(int signal) {
  if (!(signal & CURSOR_MOVED)) {
    return 0;
  }

  ++viewport_pos;

  validate_viewport();

  return 0;
}

int Console::render(const Buffer &buffer) {
  clear();

  // get cursor info
  int cursor_piece = buffer.get_cursor_piece();
  int cursor_line = buffer.get_cursor_line();
  int cursor_pos = buffer.get_cursor_pos();

  // find segment of line to render
  int line_start = cursor_pos - viewport_pos;


  // find piece that reaches top of viewport
  int cur_piece = cursor_piece;
  int cur_line = cursor_line;
  while (cur_line < viewport_line) {
    // if at top of viewport then set viewport
    if (cur_piece == 0) {
      viewport_line = cur_line;
      break;
    }

    --cur_piece;
    cur_line += buffer.get_piece(cur_piece).num_lines();
  }

  // render text
  int cur_rel_line = viewport_line - cur_line;
  while (cur_rel_line < height) {
    // stop at end of buffer
    if (cur_piece >= buffer.num_pieces()) {
      break;
    }

    const std::vector<std::string> lines = buffer.get_lines(cur_piece);
    for (const std::string& line : lines) {
      // skip lines above viewport
      if (cur_rel_line < 0) {
        ++cur_rel_line;
        continue;
      }

      // stop at end of viewport
      if (cur_rel_line >= height) {
        ++cur_rel_line;
        break;
      }

      // skip if out of view
      if (line_start >= (int) line.length()) {
        ++cur_rel_line;
        continue;
      }

      // compute segment length
      int line_len = width;
      if ((int) line.length() - line_start < line_len) {
        line_len = (int) line.length() - line_start;
      }
      
      mvprintw(cur_rel_line, 0, line.substr(line_start, line_len).c_str());

      ++cur_rel_line;
    }

    ++cur_piece;
  }

  move(viewport_line, viewport_pos);

  refresh();

  return 0;
}
