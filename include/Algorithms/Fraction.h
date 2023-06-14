#pragma once

class Fraction {
private:
   int num, den;

public:
   Fraction(int num, int den) : num(num), den(den) {};

   int multiplyInt(int number);
   Fraction multiplyFrac(Fraction frac);
};
