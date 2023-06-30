#include "buffer.h"
#include <ncurses.h>

#include <bits/stdc++.h>

#define TAB_SIZE 2

int Buffer::insert_char(Cursor& cursor, int ch) {
  int r = cursor.get_r();
  int c = cursor.get_c();

  if (r >= (int) buffer.size() || c > (int) buffer[r].length()) return 1;

  std::string prefix = buffer[r].substr(0, c);
  std::string suffix = buffer[r].substr(c);

  switch (ch) {
    case KEY_ENTER: case '\n': {
      buffer[r] = prefix;
      buffer.insert(buffer.begin() + r + 1, suffix);
      cursor.set_r(r + 1);
      cursor.set_c(0);
    }
    break;

    case '\t': {
      int gap = TAB_SIZE - prefix.length() % TAB_SIZE;
      buffer[r] = prefix + std::string(gap, ' ') + suffix;
      cursor.set_c(c + gap);
    }
    break;

    default: {
      buffer[r] = prefix + (char) ch + suffix;
      cursor.set_c(c + 1);
    }
    break;
  }

  return 0;
}

#include <bits/stdc++.h>

int Buffer::backspace(Cursor& cursor) {
  int r = cursor.get_r();
  int c = cursor.get_c();

  if (r >= (int) buffer.size() || c > (int) buffer[r].length()) return 1;

  if (c == 0) {
    if (r == 0) {
      return 0;
    }

    int nc = buffer[r - 1].length();
    buffer[r - 1] += buffer[r];
    buffer.erase(buffer.begin() + r);
    cursor.set_r(r - 1);
    cursor.set_c(nc);
  } else {
    std::string prefix = buffer[r].substr(0, c - 1);
    std::string suffix = buffer[r].substr(c);

    buffer[r] = prefix + suffix;
    if (suffix.length() == 0) {
      cursor.set_c(c - 1);
    }
  }

  return 0;
}
