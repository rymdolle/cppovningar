#include <iostream>
#include <ctime>

int main() {
  std::srand(std::time(nullptr));
  int total;
  int result[6] = {};
  std::cout << "Ange antal random tal: ";
  std::cin >> total;
  for (int i = 0; i < total; i++) {
    if (i % 10 == 0)
      std::cout << '\n';

    int nummer = std::rand() % 6;
    result[nummer]++;
    std::cout << nummer + 1 << ' ';
  }

  std::cout << '\n' << '\n';
  for (int i = 0; i < 6; i++) {
    std::cout << i + 1 << ": " << result[i]
              << " (" << (result[i]) / static_cast<float>(total) << ")"
              << std::endl;
  }
  std::cout << '\n';
  return 0;
}
