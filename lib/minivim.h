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
  std::vector<std::string> mode_strings;
  std::vector<std::map<int, Command*>> commands;
  std::vector<std::map<int, int>> mode_transitions;

public: 
  Minivim() : 
    mode(NORMAL_MODE), 
    buffer(), 
    console(buffer), 
    mode_strings(NUM_MODES), 
    commands(NUM_MODES), 
    mode_transitions(NUM_MODES) {}

  Minivim(std::string filename) : 
    mode(NORMAL_MODE), 
    buffer(filename), 
    console(buffer), 
    mode_strings(NUM_MODES), 
    commands(NUM_MODES),
    mode_transitions(NUM_MODES) {}

  ~Minivim() {
    for (std::map<int, Command*> mode_commands : commands) {
      for (std::pair<int, Command*> entry : mode_commands) {
        Command* command = entry.second;
        delete command;
      }
    }
  }

  int init();

  int render();

  int run();
};

#endif
