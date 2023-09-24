#pragma once
#include <iostream>

class Number {
private:
	unsigned int numerator;		// ·Ö×Ó
	unsigned int denominator;	// ·ÖÄ¸
public:
	Number(unsigned int _numerator);
	Number(unsigned int _numerator, unsigned int _denominator);
	inline unsigned int getNum() const { return numerator; }
	inline unsigned int getDen() const { return denominator; }

	Number operator+(const Number& other) {
		if (denominator == other.denominator) return Number(numerator + other.numerator, denominator);
		return Number(numerator * other.denominator + other.numerator * denominator, denominator* other.denominator);
	}

	Number operator*(const Number& other) {
		return Number(numerator * other.numerator, denominator * other.denominator);
	}

	Number operator/(const Number& other) {
		if (other.numerator == 0) std::cerr << "can't devide by zero.";
		else return Number(numerator * other.denominator, denominator * other.numerator);
	}
};



std::ostream& operator<< (std::ostream& out, Number& num) {
	if (num.getDen() == 1)
		out << num.getNum();
	else if(num.getNum() < num.getDen()) 
		out << num.getNum() << "/" << num.getDen();
	else
		out << num.getNum() / num.getDen() << "'" 
		<< num.getNum() - num.getNum() / num.getDen() 
		<< "/" << num.getDen();
	return out;
}