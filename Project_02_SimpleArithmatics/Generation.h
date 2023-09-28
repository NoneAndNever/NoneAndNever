#pragma once
#include "Operator.h"
#include <random>
#include <vector>
#include "Arithmetics.h"

class Generation {
private:


	std::vector<int> NumGeneration(int numLimit);
	std::vector<char> OperatorGeneration();
	std::string Combination(std::vector<int>& numList, std::vector<char>& operaList);


public:
	int numLimit;
	int request;
	Generation(int numLimit_data, int request_data) {
		numLimit = numLimit_data;
		request = request_data;
	}
	void IOsystem(void);
	void Compare(void);
};