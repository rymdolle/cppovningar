#include <iostream>
#include "ovning17.hpp"

int main()
{
  double radie;
  std::cout << "Mata in radien på en cirkel i meter: ";
  std::cin >> radie;
  std::cout << "Omkretsen är då " << omkrets(radie) << "m." << std::endl;
  std::cout << "Arean är då " << area(radie) << "m^2." << std::endl;
  return 0;
}
