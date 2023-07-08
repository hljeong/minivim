#include "buffer.h"
#include "command.h"
#include <fstream>

Buffer::Buffer(std::string filename) : 
  sources(), 
  pieces() {
  std::vector<std::string> lines;
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    lines.push_back("");
  }
  sources.push_back(lines);
  pieces.push_back(Piece(0, 0, lines.size()));
}

Command* Buffer::split(int piece, int line, bool remove_line) {
  const Piece& cur_piece = pieces[piece];
  auto it = pieces.erase(pieces.begin() + piece);
  int n_pieces = 0;

  if (line) {
    Piece piece(cur_piece.source, cur_piece.start, line);
    pieces.insert(it, piece);
    ++it;
    ++n_pieces;
  }

  if (line + remove_line < cur_piece.lines) {
    Piece piece(
      cur_piece.source, 
      cur_piece.start + (line + remove_line), 
      cur_piece.lines - (line + remove_line)
    );
    pieces.insert(it, piece);
    ++n_pieces;
  }

  return new Unsplit(piece, line, n_pieces, cur_piece);
}

Command* Buffer::unsplit(int piece, int line, int n_pieces, Piece orig_piece) {
  auto it = pieces.begin() + piece;
  int lines = 0;
  for (int i = 0; i < n_pieces; ++i) {
    lines += it->lines;
    it = pieces.erase(it);
  }

  pieces.insert(it, orig_piece);

  return new Split(piece, line, orig_piece.lines > lines);
}

Command* Buffer::insert(int index, std::vector<std::string> source) {
  sources.push_back(source);

  Piece piece(sources.size() - 1, 0, source.size());
  pieces.insert(pieces.begin() + index, piece);

  return new Uninsert(index);
}

Command* Buffer::uninsert(int index) {
  pieces.erase(pieces.begin() + index);

  std::vector<std::string> source = sources.back();
  sources.pop_back();

  return new Insert(index, source);
}
