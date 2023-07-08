#include <ncurses.h>
#include "console.h"

Console::Console() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

Console::~Console() {
  endwin();
}

int Console::get_height() const {
  return getmaxy(stdscr);
}

int Console::get_width() const {
  return getmaxx(stdscr);
}

int Console::get_char() const {
  return getch();
}

int Console::clear_screen() const {
  return clear();
}

int Console::render(const Buffer& buffer, const Config& config, const Viewport& viewport) const {
  if (config.line_nums) {
    // todo
  }

  for (int i = 0; i < viewport.height; ++i) {
    std::string line = config.render_str(buffer.get_line(viewport.line + i));

    // skip if out of view
    if (viewport.pos >= (int) line.length()) {
      continue;
    }

    // compute segment length
    int line_len = viewport.width;
    if ((int) line.length() - viewport.pos < line_len) {
      line_len = (int) line.length() - viewport.pos;
    }
    
    // render line
    mvaddstr(
      viewport.at_line + i, 
      viewport.at_pos, 
      line.substr(viewport.pos, line_len).c_str()
    );
  }

  return 0;
}

int Console::render(const CommandBuffer& command_buffer) const {
  return 0;
}

int Console::render_cursor(const Buffer& buffer, const Config& config, const Cursor& cursor, const Viewport& viewport) const {
  int line_num = buffer.get_line_num(cursor.piece, cursor.line);
  int pos = config.render_pos(buffer.get_line(line_num), cursor.pos);
  return move(
    viewport.at_line + (line_num - viewport.line), 
    viewport.at_pos + (pos - viewport.pos)
  );
}

int Console::render_cursor(const CommandBuffer& command_buffer) const {
  return 0;
}

int Console::render_to_screen() const {
  return refresh();
}
