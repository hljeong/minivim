#ifndef COMMAND_H
#define COMMAND_H

#include "buffer.h"
#include "config.h"
#include "console.h"
#include "cursor.h"
#include "viewport.h"

class Command {
public: 
  virtual ~Command() {}

  virtual Command* execute(
    Buffer &buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console &console, 
    Cursor& cursor, 
    Viewport& viewport) = 0;
};

class Nop : public Command {
public: 
  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    return new Nop();
  }
};

class Compound : public Command {
  std::vector<Command*> commands;

public: 
  Compound(std::initializer_list<Command*> commands) : commands(commands) {}

  Compound(std::vector<Command*> commands) : commands(commands) {}

  ~Compound() {
    for (Command* command : commands) {
      delete command;
    }
  }

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    std::vector<Command*> inv;
    for (Command* command : commands) {
      inv.push_back(command->execute(
        buffer, 
        command_buffer, 
        config, 
        console, 
        cursor, 
        viewport
      ));
    }

    return new Compound(inv);
  }
};

class Jump : public Command {
  int to_piece;
  int to_line;
  int to_pos;

public: 
  Jump(int to_piece, int to_line, int to_pos) : 
    to_piece(to_piece), 
    to_line(to_line), 
    to_pos(to_pos) {}

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    int from_piece = cursor.piece;
    int from_line = cursor.line;
    int from_pos = cursor.pos;
    
    cursor.piece = to_piece;
    cursor.line = to_line;
    cursor.pos = to_pos;

    return new Jump(from_piece, from_line, from_pos);
  }
};

class Split : public Command {
  int piece;
  int line;
  bool remove_line;

public: 
  Split(int piece, int line, bool remove_line) : 
    piece(piece), 
    line(line), 
    remove_line(remove_line){}

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    return buffer.split(piece, line, remove_line);
  }
};

class Unsplit : public Command {
  int piece;
  int line;
  int n_pieces;
  Piece orig_piece;

public: 
  Unsplit(int piece, int line, int n_pieces, Piece orig_piece) : 
    piece(piece), 
    line(line), 
    n_pieces(n_pieces), 
    orig_piece(orig_piece) {}

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    return buffer.unsplit(piece, line, n_pieces, orig_piece);
  }
};

class Insert : public Command {
  int index;
  std::vector<std::string> source;

public: 
  Insert(int index, std::vector<std::string> source) : 
    index(index), 
    source(source) {}

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    return buffer.insert(index, source);
  }
};

class Uninsert : public Command {
  int index;

public: 
  Uninsert(int index) : 
    index(index) {}

  Command* execute(
    Buffer& buffer, 
    CommandBuffer& command_buffer, 
    Config& config, 
    const Console& console, 
    Cursor& cursor, 
    Viewport& viewport) {
    return buffer.uninsert(index);
  }
};

#endif
