#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <ctime>

// new[] / delete[]

int main(int argc, char *argv[])
{
  std::srand(std::time(nullptr));
  int count;
  std::cout << "Enter rand count: ";
  std::cin >> count;
  int *arr = new int[count];
  long sum = 0;
  for (int i = 0; i < count; ++i) {
    arr[i] = rand() % 100; // limit to [0, 100)
    sum += arr[i];
    std::cout << std::setw(4) << i + 1 << ' ' << arr[i] << '\n';
  }

  delete[] arr;

  std::cout << "sum: " << sum << '\n';
  std::cout << "avg: " << sum / count << '\n';
  return 0;
}
