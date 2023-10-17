#ifndef _OVNING17_HPP_
#define _OVNING17_HPP_

//U+03C0
double π = 3.;
//extern "C" {
inline
double mult(double a, double b) {
  return a * b;
}

inline
double area(double radie) {
  return π * mult(radie, radie);
}

inline
double omkrets(double radie) {
  return π * mult(radie, 2);
}
//}
#endif /* _OVNING17_HPP_ */
