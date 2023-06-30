#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include "cursor.h"

class Buffer {
  std::vector<std::string> buffer;

public: 
  Buffer() : buffer(1, "") {}

  ~Buffer() {}

  std::vector<std::string>& get_buffer_ref() {
    return buffer;
  }

  int insert_char(Cursor &cursor, int ch);

  int backspace(Cursor &cursor);
};

#endif
