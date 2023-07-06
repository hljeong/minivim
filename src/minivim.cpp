#include <ncurses.h>
#include "commands.h"
#include "minivim.h"

int Minivim::run() {
  int ch;

  while (1) {
    switch (ch = console.get_char()) {
      case KEY_F(4): {
        return 0;
      }
      break;

      case KEY_UP: {
        CursorUp cursor_up;
        cursor_up.execute(buffer, console);
      }
      break;

      case KEY_DOWN: {
        CursorDown cursor_down;
        cursor_down.execute(buffer, console);
      }
      break;

      case KEY_LEFT: {
        CursorLeft cursor_left;
        cursor_left.execute(buffer, console);
      }
      break;

      case KEY_RIGHT: {
        CursorRight cursor_right;
        cursor_right.execute(buffer, console);
      }
      break;

      case KEY_BACKSPACE: {
        Backspace backspace;
        backspace.execute(buffer, console);
      }
      break;

      case '\n': {
        Linefeed linefeed;
        linefeed.execute(buffer, console);
      }
      break;

      default: {
        InsertChar insert_char(ch);
        insert_char.execute(buffer, console);
      }
      break;
    }
    console.render(buffer);
  }

  return 0;
}
