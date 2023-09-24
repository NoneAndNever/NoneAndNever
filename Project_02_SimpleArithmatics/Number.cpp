#include "Number.h"

int gcd(unsigned int a, unsigned int b) {
	return b == 0 ? gcd(b, a % b) : a;
}

Number::Number(unsigned int _numerator)
{
	numerator = _numerator;
	denominator = 1;
}

Number::Number(unsigned int _numerator, unsigned int _denominator)
{
	if (_denominator == 1) {
		numerator = _numerator;
		denominator = _denominator;
	}
	else {
		int gcd_num = gcd(_numerator, _denominator);
		numerator = _numerator / gcd_num;
		denominator = _denominator / gcd_num;
	}
}
