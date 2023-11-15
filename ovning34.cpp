#include <iostream>
#include <cstring>

void reverse(char* text, size_t length)
{
  char *end = text + length - 1;
  for (int i = 0; (text+i) < (end-i); ++i) {
    char tmp = *(text+i);
    *(text+i) = *(end-i);
    *(end-i) = tmp;
  }
}

int main(int argc, char *argv[])
{
  char *text = new char[80];
  std::cout << "Enter text: ";
  std::cin.getline(text, 80);

  int length = strlen(text);
  reverse(text, length);
  std::cout << "Reverse: " << text << "\n";

  delete[] text;
  return 0;
}
