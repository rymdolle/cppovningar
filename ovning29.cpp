#include <iostream>

int main(int argc, char *argv[])
{
  int a;
  int* p = &a;


  std::cout << "Mata in ett heltal: ";
  std::cin >> a;

  std::cout << a << "\n";
  std::cout << &a << "\n";
  std::cout << p << "\n";

  return 0;
}
