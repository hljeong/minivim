#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"

class Compound : public Command {
  std::vector<Command*> commands;

public: 
  Compound(std::initializer_list<Command*> commands) : commands(commands) {}

  ~Compound() {
    for (Command* command : commands) {
      delete command;
    }
  }

  int execute(Buffer& buffer, Console& console) {
    for (Command* command : commands) {
      command->execute(buffer, console);
    }

    return 0;
  }
};

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

class Tab : public Command {
public: 
  Tab() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.tab();
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
  int block;

public: 
  CursorRight(int block) : block(block) {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_right(block);
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

class CursorNormalize : public Command {
public: 
  CursorNormalize() {}

  int execute(Buffer& buffer, Console& console) {
    buffer.cursor_normalize();
    console.move_viewport_to_cursor(buffer);

    return 0;
  }
};

#endif
