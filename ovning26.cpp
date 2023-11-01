#include <iostream>
#include <cstring>

// 9.1
// Skriv ett program som läser in 20 heltal, lagrar dem i en array och
// skriver ut dem i omvänd ordning.
void ovning91()
{
  int array[20];
  std::cout << "Mata in 20 heltal.\n";
  for (int i = 0; i < 20; i++)
    std::cin >> array[i];

  for (int i = 0; i < 20; i++)
    std::cout << array[19 - i] << " ";

  std::cout << std::endl;

}

// 9.2
// Skriv ett program som läser in en text, lagrar den i en array av
// char och skriver ut den baklänges. Utveckla en teknik för att ta
// reda på den aktuellt in-matade char-arrayens exakta längd.
void ovning92()
{
  char text[80];
  std::cout << "Skriv en text: ";
  std::cin.getline(text, 80);

  int size = strlen(str);
  std::cout << "Texten är " << size << " tecken.\n";
  for (int i = size - 1; i >= 0; i--)
    std::cout << str[i];

  free(str);
  std::cout << std::endl;
}

// 9.3
// Skriv ett program som läser in text i gemener, lagrar den i en
// array av char och skriver ut den framhävd i versaler och med
// mellanslag mellan varje tecken. Gör som i övn 8.2 angående arrayens
// längd.
void ovning93()
{
  char str[100];
  std::cout << "Skriv ett ord med gemener: ";
  std::cin.getline(str, 100);
  //std::cin >> str;
  int size = strlen(str);
  for (int i = 0; i < size; i++)
    std::cout << static_cast<char>(str[i] & ~0b00100000) << " "; // uppercase
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  //ovning91();
  //ovning92();
  ovning93();
  return 0;
}
