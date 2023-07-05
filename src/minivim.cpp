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
