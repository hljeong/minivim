#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"

#define BACKSPACE_CROSS_LINE (1 << 31)
#define BACKSPACE_DO_NOTHING (1 << 30)
#define BACKSPACE_CROSS_LINE_DELTA_MASK ((1 << 30) - 1)

class Backspace : public Command {
public: 
  Backspace() {}

  int execute(Buffer& buffer, Console& console) {
    console.backspace(buffer.backspace());

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

#endif
