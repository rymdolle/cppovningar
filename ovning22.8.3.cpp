#include <iostream>
#include <iomanip>
#include <vector>

class Fish {
public:
  std::string type;
  int weight;
  float length;

  Fish(std::string type, int weight, float length) {
    this->type = type;
    this->weight = weight;
    this->length = length;
  }

  float price(float hekto_price) {
    return weight * (hekto_price / 100);
  }

  float freight(float vprice, float lprice) {
    return vprice * weight + lprice * length;
  }
};

int main()
{
  std::vector<Fish> fiskar = {
    Fish("Rainbow trout",  719, 38.5f),
    Fish("Atlantic cod",   423, 28.7),
    Fish("European perch", 550, 25.2),
    Fish("Northern pike",  622, 41.7),
    Fish("Zander",         382, 35.9),
  };

  std::cout << std::setw(17) << std::left << "Type"
            << std::setw(10) << std::left << "Weight"
            << std::setw(10) << std::left << "Length"
            << std::setw(10) << std::left << "Price"
            << std::setw(10) << std::left << "Freight"
            << std::endl;
  std::cout << "------------------------------------------------------" << std::endl;

  for (auto f : fiskar) {
    std::cout << std::setw(17) << std::left << f.type
              << std::setw(10) << f.weight
              << std::setw(10) << std::fixed << std::setprecision(2) << f.length
              << std::setw(10) << std::fixed << std::setprecision(2) << f.price(7.25f)
              << std::setw(10) << std::fixed << std::setprecision(2) << f.freight(0.01f, 0.02f)
              << std::endl;
  }
  return 0;
}
