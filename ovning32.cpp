#include <iostream>
int main()
{
  const char* text = "Kalle Anka";

  std::cout << "Index\tTecken\tASCII-kod\n-----------------\n";
  int i = 0;
  do {
    std::cout << i << "\t"
              << *(text+i) << '\t'
              << static_cast<int>(*(text+i)) << '\n';
  } while (*(text + i++) != '\0');
}
