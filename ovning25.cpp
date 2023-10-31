#include <iostream>

class Restid
{
public:
  int tim, min;
  Restid sum(Restid t) // Metod med objekt som parameter
  { // och objekt som returvärde
    Restid temp;
    temp.min = (min + t.min) % 60;
    temp.tim = (tim + t.tim) + (min + t.min)/60;
    return temp;
  }
};

int main(int argc, char *argv[])
{
  //Restid dagar[3];

  //std::cout << "Ange timmar och minuter till tisdagsresan: ";
  //std::cin >> dagar[0].tim >> dagar[0].min;
  //std::cout << "Ange timmar och minuter till onsdagsresan: ";
  //std::cin >> dagar[1].tim >> dagar[1].min;

  //Restid tvadagsresa = dagar[0].sum(dagar[1]); // 1:a anrop av sum
  //std::cout << "\n\tTvå dagars resa tog " << tvadagsresa.tim
  //          << " timmar och " << tvadagsresa.min << " minuter.\n\n";
  //
  //std::cout << "Ange timmar och minuter till torsdagsresan: ";
  //std::cin >> dagar[2].tim >> dagar[2].min;

  Restid vecka[7];
  Restid total = {};
  for (int i = 0; i < 7; i++) {
    std::cout << "Ange timmar och minuter för resan till dag " << i + 1 << ": ";
    std::cin >> vecka[i].tim >> vecka[i].min;
    total = total.sum(vecka[i]);
  }

  std::cout << "Total restid blir "
            << total.tim << " timmar och "
            << total.min << " minuter.\n";

  return 0;
}
