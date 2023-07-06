#include <ncurses.h>
#include "commands.h"
#include "minivim.h"

int Minivim::init() {
  commands[INSERT_MODE][KEY_UP] = new CursorUp();
  commands[INSERT_MODE][KEY_DOWN] = new CursorDown();
  commands[INSERT_MODE][KEY_LEFT] = new CursorLeft();
  commands[INSERT_MODE][KEY_RIGHT] = new CursorRight(0);

  commands[INSERT_MODE][KEY_BACKSPACE] = new Backspace();
  commands[INSERT_MODE]['\n'] = new Linefeed();
  commands[INSERT_MODE]['\t'] = new Tab();

  // todo: magic number escape keycode
  commands[INSERT_MODE][27] = new CursorNormalize();

  // todo: magic number escape keycode
  mode_transitions[INSERT_MODE][27] = NORMAL_MODE;

  // todo: magic number printable characters
  for (int printable = 32; printable <= 126; ++printable) {
    commands[INSERT_MODE][printable] = new InsertChar(printable);
  }

  commands[NORMAL_MODE]['k'] = new CursorUp();
  commands[NORMAL_MODE]['j'] = new CursorDown();
  commands[NORMAL_MODE]['h'] = new CursorLeft();
  commands[NORMAL_MODE]['l'] = new CursorRight(1);

  commands[NORMAL_MODE]['a'] = new CursorRight(0);

  mode_transitions[NORMAL_MODE]['i'] = INSERT_MODE;
  mode_transitions[NORMAL_MODE]['a'] = INSERT_MODE;

  return 0;
}

int Minivim::run() {
  int ch;
  console.render(buffer);

  while (1) {
    ch = console.get_char();

    if (ch == KEY_F(4)) {
      return 0;
    }

    if (commands[mode].find(ch) != commands[mode].end()) {
      commands[mode][ch]->execute(buffer, console);
    }

    if (mode_transitions[mode].find(ch) != mode_transitions[mode].end()) {
      mode = mode_transitions[mode][ch];
    }

    console.render(buffer);
  }

  return 0;
}
