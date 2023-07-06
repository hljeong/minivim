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

  int get_absolute_cursor_line() const {
    int line = 0;
    for (int i = 0; i < cursor.piece; ++i) {
      line += pieces[i].num_lines();
    }
    line += cursor.line;
    return line;
  }

  int get_rendered_cursor_pos(int tab_size) const {
    int pos = 0;
    const std::string& cur_line = sources[pieces[cursor.piece].get_source()][cursor.line];
    for (int i = 0; i < cursor.pos; ++i) {
      if (cur_line[i] == '\t') {
        pos += tab_size - pos % tab_size;
      } else {
        ++pos;
      }
    }
    return pos;
  }

  const Piece& get_piece(int index) const {
    return pieces[index];
  }

  int num_pieces() const {
    return pieces.size();
  }

  const int get_num_lines() const {
    int lines = 0;
    for (Piece piece : pieces) {
      lines += piece.num_lines();
    }
    return lines;
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

  int insert_char(int ch);

  int linefeed();

  int tab();

  int cursor_up();

  int cursor_down();

  int cursor_left();

  int cursor_right(int block);

  int cursor_normalize();
};

#endif
