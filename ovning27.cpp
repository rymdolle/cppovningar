#include <iostream>

void initialer(char namn[]);

// 9.4
// Skriv ett program som frågar efter användarens för- och efternamn,
// hälsar sedan användaren i en utskrift med fullständiga namnet,
// förnamnets längd samt efternamnets första och sista bokstav. Lös
// uppgiften generellt utan att använda information om något speciellt
// för- och efternamn.
int main(int argc, char *argv[])
{
  char namn[80];
  std::cout << "Mata in ditt för- och efternamn: ";
  std::cin.getline(namn, 80);

  int fn = 0;
  while (namn[fn] != ' ')
    fn++;
  int en = 0;
  while (namn[fn + en + 1] != '\0')
    en++;

  std::cout << "Hej " << namn << "!\n";
  std::cout << "Ditt förnamn är "   << fn << " tecken.\n";
  std::cout << "Ditt efternamn är " << en << " tecken.\n\n";

  std::cout << "Första bokstaven i efternamnet är '" << namn[fn+1]  << "'.\n";
  std::cout << "Sista bokstaven i efternamnet är '"  << namn[fn+en] << "'.\n";

  initialer(namn);

  return 0;
}

// 9.5
// Skriv ett program där main() läser in en persons fullständiga namn
// och hälsar tillbaka med namnets initialer. Dessa ska bestämmas och
// skrivas ut i en annan funktion – med huvudet void initialer(char[]
// namn) – som anropas i main().
void initialer(char namn[])
{
  int i = 0;
  std::cout << "Dina initialer är " << static_cast<char>(namn[i] & ~0b00100000);
  while (namn[i++] != ' ');
  std::cout << static_cast<char>(namn[i] & ~0b00100000) << ".\n";
}
