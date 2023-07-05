#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>

class Piece {
  int source;
  int start;
  int lines;

public: 
  Piece(int source, 
        int start, 
        int lines) : 
        source(source), 
        start(start), 
        lines(lines) {}

  ~Piece() {}

  int get_source() const {
    return source;
  }

  int get_start() const {
    return start;
  }

  int num_lines() const {
    return lines;
  }
};

#endif
