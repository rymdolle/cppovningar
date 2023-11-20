#include <iostream>
#include <cstring>
#include <chrono>

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

void reverse_example(char *text, size_t length)
{
  char* tmp = new char[length];
  for (size_t i = 0; i < length; ++i)
    *(tmp+i) = *(text+length-i-1);
  for (size_t i = 0; i < length; ++i)
    *(text+i) = *(tmp+i);
  delete[] tmp;
}

void reverse_pointer(char **text, size_t length)
{
  char *tmp = new char[length];
  char *end = *text + (length - 1);
  for (size_t i = 0; i < length; ++i)
    tmp[i] = *(end-i);
  delete[] *text;
  *text = tmp;
}

typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint_t;

timepoint_t start_time()
{
  return std::chrono::high_resolution_clock::now();
}

double end_time(timepoint_t start)
{
  auto now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::nano> ns_double = now - start;
  return ns_double.count() / 1000000.0;
}

int main(int argc, char *argv[])
{
  size_t size = 80;
  if (argc <= 1) {
    char *text = new char[size];
    std::cout << "Enter text:\t";
    std::cin.getline(text, 80);
    std::cout << "Before:\t\t" << text << '\n';
    size_t length = strlen(text);
    reverse(text, length);
    std::cout << "After:\t\t" << text << '\n';
    return 0;
  }

  size = std::strtol(argv[1], nullptr, 10);
  char *text = new char[size];
  for (size_t i = 0; i < size; ++i) {
    switch (i % 3) {
    case 0:
      text[i] = 'a';
      break;
    case 1:
      text[i] = 'b';
      break;
    case 2:
      text[i] = 'c';
      break;
    }
  }

  size_t length = size;

  timepoint_t start = start_time();
  std::srand(std::time(nullptr));
  int random = std::rand();
  std::cout << "random: " << random << '\n';

  for (int i = 0; i < 4; ++i) {
    if (random % 4 == 0) {
      reverse(text, length);

      start = start_time();
      reverse(text, length);
      std::cout << "reverse:\t" << end_time(start) << '\n';
    } else if (random % 4 == 1) {
      reverse_array(text, length);

      start = start_time();
      reverse_array(text, length);
      std::cout << "array:\t\t" << end_time(start) << '\n';
    } else if (random % 4 == 2) {
      reverse_example(text, length);

      start = start_time();
      reverse_example(text, length);
      std::cout << "example:\t" << end_time(start) << '\n';
    } else if (random % 4 == 3) {
      reverse_pointer(&text, length);

      start = start_time();
      reverse_pointer(&text, length);
      std::cout << "pointer:\t" << end_time(start) << '\n';
    }
    ++random;
  }
  delete[] text;
  return 0;
}
