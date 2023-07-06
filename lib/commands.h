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
    int signal = buffer.backspace();
    console.backspace(signal);

    return 0;
  }
};

class InsertChar : public Command {
  int ch;

public: 
  InsertChar(int ch) : ch(ch) {}

  int execute(Buffer& buffer, Console& console) {
    buffer.insert_char(ch);
    console.insert_char();

    return 0;
  }
};

class Linefeed : public Command {
public: 
  Linefeed() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.linefeed();
    console.linefeed();

    return 0;
  }
};

class CursorUp : public Command {
public: 
  CursorUp() {}

  int execute(Buffer& buffer, Console& console) {
    int signal = buffer.cursor_up();
    console.cursor_up(signal);

    return 0;
  }
};

class CursorDown : public Command {
public: 
  CursorDown() {}

  int execute(Buffer& buffer, Console& console) {
    int signal = buffer.cursor_down();
    console.cursor_down(signal);

    return 0;
  }
};

class CursorLeft : public Command {
public: 
  CursorLeft() {}

  int execute(Buffer& buffer, Console& console) {
    int signal = buffer.cursor_left();
    console.cursor_left(signal);

    return 0;
  }
};

class CursorRight : public Command {
public: 
  CursorRight() {}

  int execute(Buffer& buffer, Console& console) {
    int signal = buffer.cursor_right();
    console.cursor_right(signal);

    return 0;
  }
};

#endif
