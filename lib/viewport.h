#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "buffer.h"
#include "config.h"

struct Viewport {
  int line;
  int pos;
  int at_line;
  int at_pos;
  int height;
  int width;

  int cursor(int cursor_line, int cursor_pos, const Buffer& buffer, const Config& config) {
    if (cursor_line < line) {
      line = cursor_line;
    } else if (cursor_line >= line + height) {
      line = cursor_line - (height - 1);
    }

    cursor_pos = config.render_pos(buffer.get_line(cursor_line), cursor_pos);
    if (cursor_pos < pos) {
      pos = cursor_pos;
    } else if (cursor_pos >= pos + width) {
      pos = cursor_pos - (width - 1);
    }

    return 0;
  }
};

#endif
