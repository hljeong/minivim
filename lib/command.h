#ifndef COMMAND_H
#define COMMAND_H

#include "buffer.h"
#include "console.h"

#include <bits/stdc++.h>

class Command {
public: 
  virtual ~Command() {
    std::cerr << "destruct" << std::endl;
  }

  virtual int execute(Buffer &buffer, Console &console) = 0;
};

#endif
