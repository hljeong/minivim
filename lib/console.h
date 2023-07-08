#ifndef CONSOLE_H
#define CONSOLE_H

#include "buffer.h"
#include "config.h"
#include "cursor.h"
#include "viewport.h"

class Console {
public: 
  Console();

  ~Console();

  int get_height() const;

  int get_width() const;

  int get_char() const;

  int clear_screen() const;

  int render(const Buffer& buffer, const Config& config, const Viewport& viewport) const;

  int render(const CommandBuffer& command_buffer) const;

  int render_cursor(const Buffer& buffer, const Config& config, const Cursor& cursor, const Viewport& viewport) const;

  int render_cursor(const CommandBuffer& command_buffer) const;

  int render_to_screen() const;
};

#endif
