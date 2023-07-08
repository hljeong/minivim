#ifndef CURSOR_H
#define CURSOR_H

struct Cursor {
  int piece;
  int line;
  int pos;

  Cursor(int piece, int line, int pos) : 
    piece(piece), line(line), pos(pos) {}
};

#endif
