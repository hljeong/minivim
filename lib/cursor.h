#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
  int r, c;

public: 
  Cursor(int r = 0, int c = 0) : r(r), c(c) {}

  ~Cursor() {}

  int get_r() const {
    return r;
  }

  void set_r(int nr) {
    r = nr;
  }

  int get_c() const {
    return c;
  } 

  void set_c(int nc) {
    c = nc;
  }
};

#endif
