#ifndef MINIVIM_H
#define MINIVIM_H

#include "buffer.h"
#include "console.h"

class Minivim {
  Buffer buffer;
  Console console;

public: 
  Minivim() : buffer(), console() {}

  Minivim(std::string filename) : buffer(filename), console() {}

  ~Minivim() {}

  int run();
};

#endif
