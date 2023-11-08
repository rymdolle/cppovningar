#include <iostream>
#include <cmath>

void sump(int* a, int* b, int* sum);
void sumv(int  a, int  b, int  sum);

// 10.2 Deklarera vanliga variabler a, b, sum och pekarvariabler som
// pekar på resp.  variabel, läs in värden till a och b via
// pekarna. Addera a och b:s värden med pekarna, lagra resultatet i
// sum och skriv ut det med hjälp av pekaren.

// 10.3 Lös övn 9.2 ovan utan en enda vanlig variabel, endast med
// pekare.
int main(int argc, char *argv[])
{
  int* a = new int;
  int* b = new int;
  int* sum = new int(0);

  std::cout << "Mata in två heltal separerade med mellanslag: ";
  std::cin >> *a >> *b;
  sump(a, b, sum);
  std::cout << *a << " + " << *b << " = " << *sum << "\n";

  return 0;
}

void sump(int* a, int* b, int* sum)
{
  *sum = *a + *b;
}

void sumv(int a, int b, int sum)
{
  sum = a + b;
}
