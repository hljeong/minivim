#ifndef CONFIG_H
#define CONFIG_H

#include <sstream>
#include <string>

struct Config {
  int tab_size = 2;
  bool line_nums = false;

  int render_pos(const std::string& line, int pos) const {
    int ret = 0;
    for (int i = 0; i < pos; ++i) {
      if (line[i] == '\t') {
        pos += tab_size - i % tab_size;
      } else {
        ++pos;
      }
    }

    return ret;
  }

  std::string render_str(const std::string& line) const {
    std::stringstream str;
    for (int i = 0; i < (int) line.length(); ++i) {
      if (line[i] == '\t') {
        int tab = tab_size - i % tab_size;
        for (int j = 0; j < tab; ++j) {
          str << ' ';
        }
      } else {
        str << line[i];
      }
    }
    
    return str.str();
  }
};

#endif
