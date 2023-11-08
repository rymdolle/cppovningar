#include <iostream>
#include <ctime>

int main(int argc, char *argv[])
{
  std::srand(std::time(nullptr));
  int secret[4] = {
    std::rand() % 10,
    std::rand() % 10,
    std::rand() % 10,
    std::rand() % 10,
  };

  char guess[4];
  bool done = false;
  do {
    std::cout << "Mata in din gissning:\n";
    std::cin >> guess[0] >> guess[1] >> guess[2] >> guess[3];
    for (int i = 0; i < 4; i++) {
      if ((guess[i] & 0xf) == secret[i]) {
        guess[i] = 'R';
        continue;
      }

      for (int j = 0; j < 4; j++) {
        if ((guess[i] & 0xf) == secret[j]) {
          guess[i] = 'S';
          break;
        }
      }
      if (guess[i] != 'S')
        guess[i] = '?';
    }
    for (int i = 0; i < 4; i++)
      std::cout << guess[i];

    if (guess[0] == 'R' &&
        guess[1] == 'R' &&
        guess[2] == 'R' &&
        guess[3] == 'R')
      done = true;
    std::cout << "\n\n";
  } while (!done);

  for (int i = 0; i < 4; i++)
    std::cout << secret[i];
  std::cout << "\n";

  return 0;
}
