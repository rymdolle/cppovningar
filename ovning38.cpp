#include <cstdint>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void cipher_xor(std::string &data, uint8_t key)
{
  for (auto &it : data)
    it ^= key;
}

void cipher_add(std::string &data, uint8_t key)
{
  for (auto &it : data)
    it += key;
}

std::string read_file(fs::path filename)
{
  std::string data;
  std::ifstream file(filename);
  for (char letter; file.get(letter);)
    data.push_back(letter);
  file.close();
  return data;
}

void write_file(fs::path filename, std::string data)
{
  std::ofstream file(filename);
  for (char c : data)
    file.put(c);
  file.close();
}

int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cout << "Insufficient arguments.\n";
    std::cout << argv[0] << " infile outfile key\n";
    exit(1);
  }

  fs::path infile  = argv[1];
  fs::path outfile = argv[2];
  uint8_t key = std::strtol(argv[3], nullptr, 10);

  std::string data = read_file(infile);
  cipher_add(data, key);
  write_file(outfile, data);

  return 0;
}
