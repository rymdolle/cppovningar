#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  std::string filename = "WriteRead.txt";

  std::ofstream wfile(filename);
  std::cout << "Write text to file and end with '.' on an empty line.\n";
  for (std::string line; std::getline(std::cin, line);) {
    if (line == ".")
      break;
    wfile << line << '\n';
  }
  wfile.close();

  std::ifstream rfile(filename);
  // Read file and print to stdout
  std::cout << "\nThis is the contents of " << filename << ":\n\n";
  char letter;
  while (rfile.get(letter))
    std::cout << letter;
  rfile.close();
  return 0;
}
