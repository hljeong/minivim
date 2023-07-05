#ifndef COMMAND_H
#define COMMAND_H

#include "buffer.h"
#include "console.h"

class Command {
public: 
  virtual int execute(Buffer &buffer, Console &console) = 0;
};

#endif
