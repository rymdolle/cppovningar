#include <iostream>
#include <vector>

int fibonacci(int n)
{
  if (n <= 1)
    return 1;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < 20; i++) {
    std::cout << fibonacci(i) << "\n";
  }

  return 0;
}
