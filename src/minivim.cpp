#include <ncurses.h>
#include "commands.h"
#include "minivim.h"

int Minivim::init() {
  commands[INSERT_MODE][KEY_UP] = new CursorUp();

  commands[INSERT_MODE][KEY_DOWN] = new CursorDown();

  commands[INSERT_MODE][KEY_LEFT] = new CursorLeft();

  commands[INSERT_MODE][KEY_RIGHT] = new CursorRight();

  commands[INSERT_MODE][KEY_BACKSPACE] = new Backspace();

  commands[INSERT_MODE]['\n'] = new Linefeed();

  commands[INSERT_MODE]['\t'] = new Tab();

  // todo: magic number printable characters
  for (int printable = 32; printable <= 126; ++printable) {
    commands[INSERT_MODE][printable] = new InsertChar(printable);
  }

  return 0;
}

int Minivim::run() {
  int ch;
  console.render(buffer);

  while (1) {
    ch = console.get_char();

    if (ch == KEY_F(4)) {
      return 0;
    } else if (commands[mode].find(ch) != commands[mode].end()) {
      commands[mode][ch]->execute(buffer, console);
    }

    console.render(buffer);
  }

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

      case '\t': {
        Tab tab;
        tab.execute(buffer, console);
      }
      break;

      // printable characters
      case 32 ... 126: {
        InsertChar insert_char(ch);
        insert_char.execute(buffer, console);
      }
      break;
    }
    console.render(buffer);
  }

  return 0;
}
