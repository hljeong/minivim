#include "buffer.h"
#include "commands.h"
#include <fstream>
#include <ncurses.h>

Buffer::Buffer(std::string filename) : 
  sources(), 
  pieces(), 
  cursor(0, 0, 0) {
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

int Buffer::backspace() {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  
  // at start of line
  if (cursor.pos == 0) {

    // at first line of piece
    if (cursor.line == 0) {

      // at start of buffer
      if (cursor.piece == 0) {
        return 0;

      // cross-piece backspace
      } else {
        const Piece& prev_piece = pieces[cursor.piece - 1];
        const std::string prev_line = sources[prev_piece.get_source()].back();

        int npos = prev_line.length();
        cur_source[0] = prev_line + cur_source[0];

        pieces[cursor.piece - 1] = Piece(
          prev_piece.get_source(), 
          prev_piece.get_start(), 
          prev_piece.num_lines() - 1
        );
        cursor.pos = npos;

        return 0;
      }

    // delete newline within piece
    } else {
      int npos = cur_source[cursor.line - 1].length();
      cur_source[cursor.line - 1] += cur_line;
      cur_source.erase(cur_source.begin() + cursor.line);

      pieces[cursor.piece] = Piece(
        cur_piece.get_source(), 
        cur_piece.get_start(), 
        cur_piece.num_lines() - 1
      );
      --cursor.line;
      cursor.pos = npos;

      return 0;
    }

  // delete a char within line
  } else {
    const std::string prefix = cur_line.substr(0, cursor.pos - 1);
    const std::string suffix = cur_line.substr(cursor.pos);

    cur_source[cursor.line] = prefix + suffix;

    --cursor.pos;
  }

  return 0;
}

int Buffer::insert_char(int ch) {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  const std::string prefix = cur_line.substr(0, cursor.pos);
  const std::string suffix = cur_line.substr(cursor.pos);
  
  cur_source[cursor.line] = prefix + (char) ch + suffix;

  ++cursor.pos;

  return 0;
}

int Buffer::linefeed() {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  const std::string prefix = cur_line.substr(0, cursor.pos);
  const std::string suffix = cur_line.substr(cursor.pos);
  
  cur_source[cursor.line] = prefix;
  cur_source.insert(cur_source.begin() + cursor.line + 1, suffix);

  pieces[cursor.piece] = Piece(
    cur_piece.get_source(), 
    cur_piece.get_start(), 
    cur_piece.num_lines() + 1
  );
  ++cursor.line;
  cursor.pos = 0;

  return 0;
}

int Buffer::tab() {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  const std::string prefix = cur_line.substr(0, cursor.pos);
  const std::string suffix = cur_line.substr(cursor.pos);
  
  // todo: magic number bad
  int tab_size = 2 - get_rendered_cursor_pos(2) % 2;
  std::string tab(tab_size, ' ');
  cur_source[cursor.line] = prefix + tab + suffix;

  cursor.pos += tab_size;

  return 0;
}

int Buffer::cursor_up() {
  // todo: magic number bad
  int rpos = get_rendered_cursor_pos(2);

  if (cursor.line == 0) {
    if (cursor.piece == 0) {
      return 0;
    } else {
      --cursor.piece;

      cursor.line = pieces[cursor.piece].num_lines() - 1;
    }
  } else {
    --cursor.line;
  }

  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  cursor.pos = 0;
  // todo: inefficient
  while (cursor.pos < (int) cur_line.length() && get_rendered_cursor_pos(2) < rpos) {
    ++cursor.pos;
  }
  
  return 0;
}

int Buffer::cursor_down() {
  // todo: magic number bad
  int rpos = get_rendered_cursor_pos(2);

  if (cursor.line == pieces[cursor.piece].num_lines() - 1) {
    if (cursor.piece == (int) pieces.size() - 1) {
      return 0;
    } else {
      ++cursor.piece;

      cursor.line = 0;
    }
  } else {
    ++cursor.line;
  }

  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  cursor.pos = 0;
  // todo: inefficient
  while (cursor.pos < (int) cur_line.length() && get_rendered_cursor_pos(2) < rpos) {
    ++cursor.pos;
  }
  
  return 0;
}

int Buffer::cursor_left() {
  if (cursor.pos > 0) {
    --cursor.pos;
    return 0;
  }
  
  return 0;
}

int Buffer::cursor_right(int block) {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];
  
  if (cursor.pos < (int) cur_line.length() - block) {
    ++cursor.pos;
    return 0;
  }
  
  return 0;
}

int Buffer::cursor_normalize() {
  const Piece& cur_piece = pieces[cursor.piece];
  std::vector<std::string>& cur_source = sources[cur_piece.get_source()];
  const std::string& cur_line = cur_source[cursor.line];

  if (cursor.pos >= (int) cur_line.length()) {
    cursor.pos = cur_line.length() - 1;
  }
  
  return 0;
}
