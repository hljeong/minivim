#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

class Command;

struct Piece {
  int source;
  int start;
  int lines;

  Piece(int source, 
    int start, 
    int lines) : 
    source(source), 
    start(start), 
    lines(lines) {}

  Piece(const Piece& piece) : 
    source(piece.source), 
    start(piece.start), 
    lines(piece.lines) {}
};

class Buffer {
  std::vector<std::vector<std::string>> sources;
  std::vector<Piece> pieces;

public: 
  Buffer() : 
    sources(), 
    pieces() {
    sources.push_back(std::vector<std::string>(1, ""));
    pieces.push_back(Piece(0, 0, 1));
  }

  Buffer(std::string filename);

  ~Buffer() {}

  int get_line_num(int piece, int line) const {
    int line_num = 0;
    for (int i = 0; i < piece; ++i) {
      line_num += pieces[i].lines;
    }
    return line_num + line;
  }
  
  std::string get_line(int line_num) const {
    for (const Piece& piece : pieces) {
      if (line_num < piece.lines) {
        return sources[piece.source][piece.start + line_num];
      } else {
        line_num -= piece.lines;
      }
    }
    return "";
  }

  Command* split(int piece, int line, bool remove_line);

  Command* unsplit(int piece, int line, int n_pieces, Piece orig_piece);

  Command* insert(int index, std::vector<std::string> source);

  Command* uninsert(int index);
};

class CommandBuffer {
  
};

#endif
