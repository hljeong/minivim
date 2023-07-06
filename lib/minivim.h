#ifndef MINIVIM_H
#define MINIVIM_H

#include <functional>
#include <map>
#include "buffer.h"
#include "command.h"
#include "console.h"

#define INSERT_MODE 0
#define NORMAL_MODE 1
#define NUM_MODES 2

class Minivim {
  int mode;
  Buffer buffer;
  Console console;
  std::vector<std::map<int, Command*>> commands;

public: 
  Minivim() : 
    mode(INSERT_MODE), 
    buffer(), 
    console(), 
    commands(NUM_MODES) {}

  Minivim(std::string filename) : 
    mode(INSERT_MODE), 
    buffer(filename), 
    console(), 
    commands(NUM_MODES) {}

  ~Minivim() {
    for (std::map<int, Command*> mode_commands : commands) {
      for (std::pair<int, Command*> entry : mode_commands) {
        Command* command = entry.second;
        delete command;
      }
    }
  }

  int init();

  int run();
};

#endif
