﻿#pragma once
#include <vector>
#include <string>
#include "Operator.h"

class Arithmetics
{
private:
	// nums and operators to do arithmetics
	std::vector<Number> nums;
	std::vector<Operator> operators;
	Number result = Number(0, 0);
public:

	// differences between three functions below
	// 
	// string_to_equation (Recommended)
	// receive string like "1+ 2*(3 - 1/ 2)" with loose space judgment
	// but can not recognize fraction
	//
	// string_with_space_to_equation
	// receive string like "1 + 2 * ( 3 - 1/2 )" with strict space judgment
	// can recognize fraction
	//
	// string_with_out_space_to_equation
	// receive string like "1+2*(3-1/2)" with strict space judgment
	// can not recognize fraction
	//

	void string_to_equation(std::string str);
	void string_with_space_to_equation(std::string str);
	void string_without_space_to_equation(std::string str);

	// output equals without space
	std::string equation_to_string() const;
public:
	// call calculate() to get result
	Number get_result();

	bool operator<(Arithmetics& other) { return get_result() < get_result(); }
	bool operator<=(Arithmetics& other) { return get_result() <= get_result(); }
	bool operator==(Arithmetics& other) { return get_result() == get_result(); }
	bool operator>=(Arithmetics& other) { return get_result() >= get_result(); }
	bool operator>(Arithmetics& other) { return get_result() > get_result(); }
	bool clear();
private:
	Number calculate();
	Number calculate_in_brace(
		std::vector<Number>::iterator& it_num,
		std::vector<Operator>::iterator& it_opr
	);
};