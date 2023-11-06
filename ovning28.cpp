#include <iostream>
#include <iomanip>
#include <cstdint>

void krypt(char text[], int key)
{
  for (int i = 0; text[i] != '\0'; i++)
    text[i] = text[i] + key;
}

int main(int argc, char *argv[])
{
  char text[100];
  std::cout << "Mata in en text att kryptera.\n";
  std::cin.getline(text, 100);
  uint8_t key = 100;

  krypt(text, key);
  for (int i = 0; text[i] != '\0'; i++)
    std::cout << std::setw(2) << std::fixed << std::hex << (int) ((text[i]) & 0xff);
  std::cout << std::endl;

  krypt(text, -key);
  for (int i = 0; text[i] != '\0'; i++)
    std::cout << text[i];
  std::cout << std::endl;
  return 0;
}
