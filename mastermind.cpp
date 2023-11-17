#include <iostream>
#include <ctime>

void create(int *secret)
{
  // generate 4 unique numbers between 0 and 9
  for (int i = 0; i < 4; ++i) {
    secret[i] = std::rand() % 10;
    for (int j = 0; j < i; ++j) {
      while (secret[i] == secret[j]) {
        secret[i] = std::rand() % 10;
      }
    }
  }
}

bool input(char *guess)
{
  // Check user input
  for (int i = 0; i < 4; i++) {
    if (guess[i] < '0' || guess[i] > '9')
      return false;

    guess[i] &= 0xf;
  }
  return true;
}

int main(int argc, char *argv[])
{
  std::srand(std::time(nullptr));
  int secret[4];
  create(secret);
  for (int i = 0; i < 4; ++i) {
    std::cout << secret[i];
  }
  std::cout << "\n";

  char guess[5] = {};
  do {
    std::cout << "Mata in din gissning med 4 tal mellan 0-9, t.ex. 1234:\n";
    std::cin >> guess[0] >> guess[1] >> guess[2] >> guess[3];
    if (!input(guess)) {
      std::cout << "Felaktig inmatning.\n";
      continue;
    }
    for (int i = 0; i < 4; i++) {
      // Check user guess for secret
      if (guess[i] == secret[i]) {
        guess[i] = 'R';
        continue;
      }

      for (int j = 0; j < 4; j++) {
        if (guess[i] == secret[j]) {
          guess[i] = 'S';
          break;
        }
      }

      if (guess[i] != 'S')
        guess[i] = '?';
    }

    std::cout << guess << '\n' << '\n';

  } while (guess[0] != 'R' ||
           guess[1] != 'R' ||
           guess[2] != 'R' ||
           guess[3] != 'R');

  std::cout << "Korrekt! Hemliga talet var ";
  for (int i = 0; i < 4; i++)
    std::cout << secret[i];
  std::cout << ".\n";

  return 0;
}
