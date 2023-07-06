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

int Console::move_viewport_to_cursor(const Buffer& buffer) {
  getmaxyx(stdscr, height, width);

  // get cursor info
  int cursor_line = buffer.get_absolute_cursor_line();
  int cursor_pos = buffer.get_rendered_cursor_pos(TAB_SIZE);

  if (cursor_line < viewport_line) {
    viewport_line = cursor_line;
  } else if (cursor_line >= viewport_line + height) {
    viewport_line = cursor_line - (height - 1);
  }

  if (cursor_pos < viewport_pos) {
    viewport_pos = cursor_pos;
  } else if (cursor_pos >= viewport_pos + width) {
    viewport_pos = cursor_pos - (width - 1);
  }

  return 0;
}

int Console::render(const Buffer &buffer) {
  clear();

  // get cursor info
  int absolute_cursor_line = buffer.get_absolute_cursor_line();
  int rendered_cursor_pos = buffer.get_rendered_cursor_pos(TAB_SIZE);

  // find first piece visible in viewport
  int cur_piece = 0;
  int cur_line = 0;
  while (cur_line + buffer.get_piece(cur_piece).num_lines() < viewport_line) {
    ++cur_piece;
    cur_line += buffer.get_piece(cur_piece).num_lines();
  }

  // render text
  while (cur_line < viewport_line + height) {
    // stop at end of buffer
    if (cur_piece >= buffer.num_pieces()) {
      break;
    }

    const std::vector<std::string> lines = buffer.get_lines(cur_piece);
    for (std::string line : lines) {
      // skip lines above viewport
      if (cur_line < viewport_line) {
        ++cur_line;
        continue;
      }

      // stop at end of viewport
      if (cur_line >= viewport_line + height) {
        ++cur_line;
        break;
      }

      // skip if out of view
      if (viewport_pos >= (int) line.length()) {
        ++cur_line;
        continue;
      }

      // replace tabs with spaces
      std::string tab(TAB_SIZE, ' ');
      size_t pos = 0;
      while((pos = line.find("\t", pos)) != std::string::npos) {
        int tab_size = TAB_SIZE - (int) pos % TAB_SIZE;
        std::string tab(tab_size, ' ');
        line.replace(pos, 1, tab);
        pos += TAB_SIZE;
      }

      // compute segment length
      int line_len = width;
      if ((int) line.length() - viewport_pos < line_len) {
        line_len = (int) line.length() - viewport_pos;
      }
      
      // render line
      mvaddstr(cur_line - viewport_line, 0, line.substr(viewport_pos, line_len).c_str());

      ++cur_line;
    }

    ++cur_piece;
  }

  move(absolute_cursor_line - viewport_line, rendered_cursor_pos - viewport_pos);

  refresh();

  return 0;
}
