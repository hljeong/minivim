#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"

#define BACKSPACE_CROSS_LINE (1 << 30)
#define BACKSPACE_DO_NOTHING (1 << 29)
#define BACKSPACE_CROSS_LINE_DELTA_MASK ((1 << 29) - 1)
#define CURSOR_MOVED (1 << 30)
#define CURSOR_POS_MASK ((1 << 30) - 1)

class Backspace : public Command {
public: 
  Backspace() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.backspace();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class InsertChar : public Command {
  int ch;

public: 
  InsertChar(int ch) : ch(ch) {}

  int execute(Buffer& buffer, Console& console) {
    buffer.insert_char(ch);
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class Linefeed : public Command {
public: 
  Linefeed() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.linefeed();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class CursorUp : public Command {
public: 
  CursorUp() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_up();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class CursorDown : public Command {
public: 
  CursorDown() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_down();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class CursorLeft : public Command {
public: 
  CursorLeft() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_left();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class CursorRight : public Command {
public: 
  CursorRight() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_right();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

#endif
