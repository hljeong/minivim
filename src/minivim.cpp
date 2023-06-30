#include "minivim.h"
#include <ncurses.h>

int Minivim::run() {
  int ch;

  while (1) {
    switch (ch = console.get_char()) {
      case KEY_F(4): {
        return 0;
      }
      break;

      case KEY_BACKSPACE: {
        buffer.backspace(console.get_cursor_ref());
      }
      break;

      default: {
        buffer.insert_char(console.get_cursor_ref(), ch);
      }
      break;
    }
    console.render(buffer.get_buffer_ref());
  }

  return 0;
}
