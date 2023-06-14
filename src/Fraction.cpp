#include "Algorithms/Fraction.h"


int Fraction::multiplyInt(int number) {
   return (num*number)/den;
}

Fraction Fraction::multiplyFrac(Fraction frac) {
   return Fraction(num*frac.num, den*frac.den);
}
