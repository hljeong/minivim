#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include "piece.h"

struct Cursor {
  int piece;
  int line;
  int pos;
  
  Cursor(int piece, int line, int pos) : 
    piece(piece), line(line), pos(pos) {}
};

class Buffer {
  std::vector<std::vector<std::string>> sources;
  std::vector<Piece> pieces;
  Cursor cursor;

public: 
  Buffer() : 
    sources(), 
    pieces(), 
    cursor(0, 0, 0) {
    sources.push_back(std::vector<std::string>(1, ""));
    pieces.push_back(Piece(0, 0, 1));
  }

  Buffer(std::string filename);

  ~Buffer() {}

  int get_cursor_piece() const {
    return cursor.piece;
  }

  int get_cursor_line() const {
    return cursor.line;
  }

  int get_cursor_pos() const {
    return cursor.pos;
  }

  const Piece& get_piece(int index) const {
    return pieces[index];
  }

  int num_pieces() const {
    return pieces.size();
  }

  const std::vector<std::string> get_lines(int index) const {
    Piece piece = pieces[index];
    std::vector<std::string> source = sources[piece.get_source()];
    return std::vector<std::string>(
      source.begin() + piece.get_start(), 
      source.begin() + piece.get_start() + piece.num_lines()
    );
  }

  int backspace();

  int linefeed();

  int insert_char(int ch);

  int cursor_up();

  int cursor_down();

  int cursor_left();

  int cursor_right();
};

#endif
