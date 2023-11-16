#include <iostream>
#include <cstring>

void reverse(char *text, size_t length)
{
  char *end = text + length - 1;
  for (size_t i = 0; (text+i) < (end-i); ++i) {
    char tmp = *(text+i);
    *(text+i) = *(end-i);
    *(end-i) = tmp;
  }
}

void reverse_array(char text[], size_t length)
{
  size_t end = length - 1;
  for (size_t i = 0; i < (end-i); ++i) {
    char tmp = text[i];
    text[i] = text[end-i];
    text[end-i] = tmp;
  }
}

int main(int argc, char *argv[])
{
  char *text = new char[80];
  std::cout << "Enter text:\t";
  std::cin.getline(text, 80);

  size_t length = strlen(text);
  reverse(text, length);
  std::cout << "Reverse:\t" << text << "\n";

  reverse_array(text, length);
  std::cout << "Reverse again:\t" << text << "\n";

  delete[] text;
  return 0;
}
