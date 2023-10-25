#include <iostream>
#include <iomanip>

class Circle {
  float radie;
public:
  Circle(float r) {
    radie = r;
  }
  float area() {
    return radie *radie * 3.1415f;
  }
  float omkrets() {
    return 2 * radie * 3.1415f;
  }
};

class Fisk {
private:
public:
  std::string sort;
  float vikt;
  float längd;
};

int main()
{
  float input;
  std::cout << "Mata in radie: ";
  //std::cin >> input;

  Circle c(2.f);
  //Circle c;
  std::cout << "Area:    " << c.area()    << std::endl;
  std::cout << "Omkrets: " << c.omkrets() << std::endl;
  std::cout << std::endl;

  Fisk f1;
  f1.sort = "Laxforell";
  f1.vikt = 719.f;
  f1.längd = 38.5f;
  Fisk f2;
  f2.sort = "Torst";
  f2.vikt = 423.f;
  f2.längd = 28.7;

  std::cout << std::setw(14) << std::left << "Sort"
            << std::setw(12) << std::left << "Vikt"
            << std::setw(12) << std::left << "Längd"
            << std::endl;

  std::cout << std::setw(14) << std::left << f1.sort
            << std::setw(12) << std::left << f1.vikt
            << std::setw(12) << std::left << f1.längd
            << std::endl;

  std::cout << std::setw(14) << std::left << f2.sort
            << std::setw(12) << std::left << f2.vikt
            << std::setw(12) << std::left << f2.längd
            << std::endl;
  return 0;
}
