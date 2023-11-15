#include <iostream>

void initialer(const char* namn)
{
  std::cout << *namn;
  while (*namn != ' ') {
    ++namn;
    if (*namn == '\0')
      return;
  }
  std::cout << *(namn+1);
}

int main()
{
  char* dittNamn = new char[80];

  std::cout << "Ge ditt för- och efternamn: ";
  std::cin.getline(dittNamn, 80);
  std::cout << "Hej " << dittNamn << ", dina initialer är: ";
  initialer(dittNamn);
  std::cout << '\n';

  char* start = dittNamn;
  char* end = start;
  // Hitta nolltecknet
  for (; *end != '\0'; end++);

  // Skriv ut baklänges
  std::cout << "Baklänges:\t";
  for (int i = 1; (end-i) >= start; i++)
    std::cout << *(end-i);
  std::cout << '\n';

  // Byt plats på första och sista bokstaven
  std::cout << "Före byte:\t" << dittNamn << "\n";
  // char first = *start; // tmp var
  // char* last = end-1;
  // *start = *last;
  // *last = first;
  std::swap(*start, *(end-1));
  std::cout << "Efter byte:\t" << dittNamn << "\n";

  delete[] dittNamn;
}
