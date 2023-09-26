#include "Arithmatics.h"



int main() {
	Arithmatics arithmatics;
	arithmatics.string_to_equation("21 + ((25/3) * 6 - 14 )");
	//arithmatics.StringWithoutSpace2Equation("1+(2/3*7-8)");
	std::string s = arithmatics.equation_to_string();
	std::string res = arithmatics.get_result().to_string();
	system("pause");
	return 0;
}