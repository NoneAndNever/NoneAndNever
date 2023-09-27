#pragma once
#include <iostream>

//if CALCULATE_DEBUG is true, the calculation procedure will be printed
#ifndef CALCULATE_DEBUG
#define CALCULATE_DEBUG true
#endif

class Number {
private:
	unsigned int numerator;		// 1 of 1/3
	unsigned int denominator;	// 3 of 1/3
public:
	Number(unsigned int _numerator);
	Number(unsigned int _numerator, unsigned int _denominator);
	inline unsigned int get_num() const { return numerator; }
	inline unsigned int get_den() const { return denominator; }
	bool is_valid() const {return get_num() < 0 || get_den() == 0;}

	std::string to_string() const;

	static Number add(const Number& A, const Number& B);
	static Number minus(const Number& A, const Number& B);
	static Number multiply(const Number& A, const Number& B);
	static Number divide(const Number& A, const Number& B);

	Number add(const Number& other) const;
	Number minus(const Number& other) const;
	Number multiply(const Number& other) const;
	Number divide(const Number& other) const;
	
	Number operator+(const Number& other);
	Number operator-(const Number& other);
	Number operator*(const Number& other);
	Number operator/(const Number& other);

	bool operator<(const Number& other) const;
	bool operator<=(const Number& other) const;
	bool operator==(const Number& other) const;
	bool operator>=(const Number& other) const;
	bool operator>(const Number& other) const;

	friend std::ostream& operator<< (std::ostream& out, Number& num);

	
};




