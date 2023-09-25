#include "Arithmatics.h"



int main() {
	Arithmatics arithmatics;
	arithmatics.String2Equation("1 + 2 / 3 * 7 - 8");
	std::string s = arithmatics.Equation2String();
	system("pause");
	return 0;
}