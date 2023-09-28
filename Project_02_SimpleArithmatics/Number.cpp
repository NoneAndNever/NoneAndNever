#include "Number.h"

#include <string>


unsigned int gcd(unsigned int a, unsigned int b) {
	return b > 0 ? gcd(b, a % b) : a;
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
		unsigned int gcd_num = gcd(_numerator, _denominator);
		numerator = _numerator / gcd_num;
		denominator = _denominator / gcd_num;
	}
}

std::string Number::to_string() const
{
	std::string res;
	if (get_den() == 1) // integer
		res += std::to_string(get_num());
	else if (get_num() < get_den()) // proper fraction (with numerator < denominator)
		res += std::to_string(get_num()) + "/" + std::to_string(get_den());
	else // improper fraction
		res += std::to_string(get_num() / get_den()) + "'" +
		std::to_string(get_num() - get_num() / get_den() * get_den()) + "/" +
		std::to_string(get_den());
	return res;
}

Number Number::add(const Number& A, const Number& B) {
	if (A.denominator == B.denominator) return Number(A.numerator + B.numerator, A.denominator);
	return Number(A.numerator * B.denominator + B.numerator * A.denominator, A.denominator * B.denominator);
}

Number Number::minus(const Number& A, const Number& B) {
	if (A.denominator == B.denominator) return Number(A.numerator - B.numerator, A.denominator);
	return Number(A.numerator * B.denominator - B.numerator * A.denominator, A.denominator * B.denominator);
}

Number Number::multiply(const Number& A, const Number& B) {
	return Number(A.numerator * B.numerator, A.denominator * B.denominator);
}

Number Number::divide(const Number& A, const Number& B) {
	if (B.numerator == 0) std::cerr << "ERROR : can't divide by zero.";
	else return Number(A.numerator * B.denominator, A.denominator * B.numerator);
}

Number Number::add(const Number& other) const
{
	if (denominator == other.denominator) return Number(numerator + other.numerator, denominator);
	return Number(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
}

Number Number::minus(const Number& other) const
{
	if (denominator == other.denominator) return Number(numerator - other.numerator, denominator);
	return Number(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
}

Number Number::multiply(const Number& other) const
{
	return Number(numerator * other.numerator, denominator * other.denominator);
}

Number Number::divide(const Number& other) const
{
	if (other.numerator == 0) std::cerr << "can't divide by zero.";
	else return Number(numerator * other.denominator, denominator * other.numerator);
	return { 0,0 };
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

bool Number::operator<(const Number& other) const
{
	return numerator * other.denominator < other.numerator * denominator;
}

bool Number::operator<=(const Number& other) const
{
	return numerator * other.denominator <= other.numerator * denominator;
}

bool Number::operator==(const Number& other) const
{
	return numerator * other.denominator == other.numerator * denominator;
}

bool Number::operator>=(const Number& other) const
{
	return numerator * other.denominator >= other.numerator * denominator;
}

bool Number::operator>(const Number& other) const
{
	return numerator * other.denominator > other.numerator * denominator;
}

std::ostream& operator<< (std::ostream& out, Number& num) {
	if (num.get_den() == 1)
		out << num.get_num();
	else if (num.get_num() < num.get_den())
		out << num.get_num() << "/" << num.get_den();
	else
		out << num.get_num() / num.get_den() << "'"
		<< num.get_num() - num.get_num() / num.get_den() * num.get_num()
		<< "/" << num.get_den();
	return out;
}

