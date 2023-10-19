#include <iostream>
#include "ovning19.hpp"

int main() {
  float rate;
  int type;

  std::cout << "Vilken moms vill du ha i procent?" << "\n";
  std::cin >> rate;
  std::cout << "Lägga till (0) eller dra av (1) moms?" << "\n";
  std::cin >> type;
  return 0;
}
