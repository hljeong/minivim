#include <ncurses.h>
#include "commands.h"
#include "console.h"

Console::Console(const Buffer& buffer) : 
  viewport_line(0), 
  viewport_pos(0) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  move_viewport_to_cursor(buffer);
}

Console::~Console() {
  endwin();
}

int Console::move_viewport_to_cursor(const Buffer& buffer) {
  getmaxyx(stdscr, window_height, window_width);

  viewport_height = window_height - 1;
  line_num_width = std::to_string(buffer.get_num_lines()).length();
  viewport_width = window_width - line_num_width - 1;

  // get cursor info
  int cursor_line = buffer.get_absolute_cursor_line();
  int cursor_pos = buffer.get_rendered_cursor_pos(TAB_SIZE);

  if (cursor_line < viewport_line) {
    viewport_line = cursor_line;
  } else if (cursor_line >= viewport_line + viewport_height) {
    viewport_line = cursor_line - (viewport_height - 1);
  }

  if (cursor_pos < viewport_pos) {
    viewport_pos = cursor_pos;
  } else if (cursor_pos >= viewport_pos + viewport_width) {
    viewport_pos = cursor_pos - (viewport_width - 1);
  }

  return 0;
}

#include <bits/stdc++.h>

int Console::render_status(const std::string& mode) {
  mvaddstr(viewport_height, 0, mode.c_str());

  std::cerr << mode << std::endl;

  return 0;
}

int Console::render_buffer(const Buffer &buffer) {
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
  while (cur_line < viewport_line + viewport_height) {
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
      if (cur_line >= viewport_line + viewport_height) {
        break;
      }

      // render line number
      std::string line_num = std::to_string(cur_line + 1);
      line_num.insert(0, line_num_width - line_num.length(), ' ');
      mvaddstr(cur_line - viewport_line, 0, line_num.c_str());

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
      int line_len = viewport_width;
      if ((int) line.length() - viewport_pos < line_len) {
        line_len = (int) line.length() - viewport_pos;
      }
      
      // render line
      mvaddstr(cur_line - viewport_line, line_num_width + 1, line.substr(viewport_pos, line_len).c_str());

      ++cur_line;
    }

    ++cur_piece;
  }

  move(absolute_cursor_line - viewport_line, line_num_width + 1 + rendered_cursor_pos - viewport_pos);

  return 0;
}
