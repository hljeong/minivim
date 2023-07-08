#ifndef MINIVIM_H
#define MINIVIM_H

#include <map>
#include <string>
#include <vector>
#include "buffer.h"
#include "command.h"
#include "config.h"
#include "console.h"
#include "cursor.h"
#include "viewport.h"

#define INSERT_MODE 0
#define NORMAL_MODE 1
#define NUM_MODES 2

class Minivim {
  Buffer buffer;
  CommandBuffer command_buffer;
  Config config;
  Console console;
  Cursor cursor;
  Viewport viewport;
  std::vector<std::string> mode_strings;
  std::vector<std::map<int, Command*>> commands;
  std::vector<std::map<int, int>> mode_transitions;

public: 
  Minivim() : 
    buffer(), 
    command_buffer(), 
    config(), 
    console(), 
    cursor(0, 0, 0), 
    viewport(), 
    mode_strings(NUM_MODES), 
    commands(NUM_MODES), 
    mode_transitions(NUM_MODES) {}

  Minivim(std::string filename) : 
    buffer(filename), 
    command_buffer(), 
    config(), 
    console(), 
    cursor(0, 0, 0), 
    viewport(), 
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

  int input(int ch);

  int render() const;

  int run();
};

#endif
