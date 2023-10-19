#include <iostream>

__attribute__((cdecl))
float vat0(float amount, float rate) {
  return amount * rate / 100.f;
}

__attribute__((stdcall))
float vat1(float amount, float rate) {
  return amount * rate / (100.f + rate);
}

void table(float rate) {
}
