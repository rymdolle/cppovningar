#include <iostream>
#include <string>

bool palindrom(std::string text) {
  int front = 0;
  int back = text.size() - 1;
  while (front < back) {
    if (text[front++] != text[back--])
      return false;
  }
  return true;
}

int main(int argc, char *argv[])
{
  std::string text;
  std::cout << "Mata in en sträng att testa för en palindrom (OBS! skiftlägeskänslig).\n";
  std::cin >> text;
  if (palindrom(text))
    std::cout << "Ordet ÄR en palindrom.\n";
  else
    std::cout << "Ordet är INTE en palindrom.\n";

  return 0;
}
