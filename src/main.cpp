#include <iostream>
#include <string>
#include "driver.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << ", FILE" << std::endl;
    return 1;
  }

  Driver drv;
  if (!drv.parse(argv[1])) {
    std::cout << drv.result << std::endl;
    return drv.result;
  }
  return 0;
}
