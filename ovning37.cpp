#include <iostream>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <climits>

std::string rand_pwd(std::string allowed, size_t length)
{
  std::string pwd;
  for (int i = 0; i < length; ++i)
    pwd.push_back(allowed[rand() % allowed.size()]);
  return pwd;
}

int main(int argc, char *argv[])
{
  srand(time(nullptr));

  std::string filename = "passwd.txt";
  int count, length;
  char letter;
  std::string allowed_chars =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789 "
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

  // Let user supply an optional output file
  if (argc > 1)
    filename = argv[1];

  if (std::filesystem::exists(filename)) {
    std::cout << "File exists. Do you want to overwrite '"
              << filename << "'? [y/N] ";
    std::cin.get(letter);
    if (letter != 'y' && letter != 'Y')
      exit(1);

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
  }

  std::cout << "How many users do you want? ";
  std::cin >> count;
  std::cout << "How long passwords do you want? ";
  std::cin >> length;

  // Generate random passwords and write to file
  std::ofstream wfile(filename);
  for (int i = 0; i < count; ++i)
    wfile << "user" << i+1 << '\t' << rand_pwd(allowed_chars, length) << '\n';
  wfile.close();

  std::cout << '\n'
            << "Here are your users with their passwords stored in '"
            << filename << "'.\n";
  // Read from file and print to stdout
  std::ifstream rfile(filename);
  while (rfile.get(letter))
    std::cout << letter;
  rfile.close();

  return 0;
}
