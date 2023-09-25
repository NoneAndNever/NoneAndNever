#include "Number.h"

#include <string>


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
	if (_numerator == 0) {
		numerator = _numerator;
		denominator = 1;
	}
	else if (_denominator == 1) {
		numerator = _numerator;
		denominator = _denominator;
	}
	else {
		int gcd_num = gcd(_numerator, _denominator);
		numerator = _numerator / gcd_num;
		denominator = _denominator / gcd_num;
	}
}

Number Number::Add(const Number& A, const Number& B) {
	if (A.denominator == B.denominator) return Number(A.numerator + B.numerator, A.denominator);
	return Number(A.numerator * B.denominator + B.numerator * A.denominator, A.denominator * B.denominator);
}

Number Number::Minus(const Number& A, const Number& B){
	if (A.denominator == B.denominator) return Number(A.numerator - B.numerator, A.denominator);
	return Number(A.numerator * B.denominator - B.numerator * A.denominator, A.denominator * B.denominator);
}

Number Number::Multiply(const Number& A, const Number& B) {
	return Number(A.numerator * B.numerator, A.denominator * B.denominator);
}

Number Number::Divide(const Number& A, const Number& B){
	if (B.numerator == 0) std::cerr << "can't divide by zero.";
	else return Number(A.numerator * B.denominator, A.denominator * B.numerator);
}

Number Number::Add(const Number& other) {
	if (denominator == other.denominator) return Number(numerator + other.numerator, denominator);
	return Number(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
}

Number Number::Minus(const Number& other) {
	if (denominator == other.denominator) return Number(numerator - other.numerator, denominator);
	return Number(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
}

Number Number::Multiply(const Number& other) {
	return Number(numerator * other.numerator, denominator * other.denominator);
}

Number Number::Divide(const Number& other) {
	if (other.numerator == 0) std::cerr << "can't divide by zero.";
	else return Number(numerator * other.denominator, denominator * other.numerator);
}

std::string Number::to_string() const
{
	std::string res;
	if (getDen() == 1)
		res += std::to_string(getNum());
	else if(getNum() < getDen())
		res += std::to_string(getNum()) + "/" + std::to_string(getDen());
	else
		res += std::to_string(getNum() / getDen()) + "'" +
				std::to_string(getNum() - getNum() / getDen() * getNum()) + "/" +
				std::to_string(getDen());
	return res;
}

Number Number::operator+(const Number& other) {
	if (denominator == other.denominator) return Number(numerator + other.numerator, denominator);
	return Number(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
}

Number Number::operator-(const Number& other) {
	if (denominator == other.denominator) return Number(numerator - other.numerator, denominator);
	return Number(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
}

Number Number::operator*(const Number& other) {
	return Number(numerator * other.numerator, denominator * other.denominator);
}

Number Number::operator/(const Number& other) {
	if (other.numerator == 0) std::cerr << "can't devide by zero.";
	else return Number(numerator * other.denominator, denominator * other.numerator);
}

Operator::Operator(const char& operatorChar)
{
	switch (operatorChar)
	{
	case '+': func = Number::Add; break;
	case '-': func = Number::Minus; break;
	case '*': func = Number::Multiply; break;
	case '/': func = Number::Divide; break;
	}
}

Operator::Operator(operatorFunc _func)
{
	func = _func;
}

std::string Operator::to_string() const
{
	if(func == Number::Add) return "+";
	if(func == Number::Minus) return "-";
	if(func == Number::Multiply) return "*";
	if(func == Number::Divide) return "/";
	return std::string();
}
