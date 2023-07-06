#include "minivim.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    Minivim minivim;
    minivim.init();
    return minivim.run();
  } else {
    std::string filename = std::string(argv[1]);
    Minivim minivim(filename);
    minivim.init();
    return minivim.run();
  }
}
