#pragma once
#include <vector>
#include <string>
#include "Number.h"

class Arithmatics
{
private:
	std::vector<Number> nums;
	std::vector<Operator> operators;
public:
	void String2Equation(std::string str);
	std::string Equation2String() const;

	
};
