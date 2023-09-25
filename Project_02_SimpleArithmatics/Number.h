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
	
	static Number Add(const Number& A, const Number& B);
	static Number Minus(const Number& A, const Number& B);
	static Number Multiply(const Number& A, const Number& B);
	static Number Divide(const Number& A, const Number& B);

	Number Add(const Number& other);
	Number Minus(const Number& other);
	Number Multiply(const Number& other);
	Number Divide(const Number& other);

	std::string to_string() const;

	Number operator+(const Number& other);
	Number operator-(const Number& other);
	Number operator*(const Number& other);
	Number operator/(const Number& other);

	friend std::ostream& operator<< (std::ostream& out, Number& num);
};


typedef Number(*operatorFunc)(const Number&, const Number&);

class Operator {
private:
	operatorFunc func;
public:
	Operator(const char& operatorChar);
	Operator(operatorFunc _func);

	std::string to_string() const;
	
	operatorFunc& operator*() {return func;}
	operatorFunc* operator->() {return &func;}
	friend  std::ostream& operator<< (std::ostream& out, Operator& o);

};

// std::ostream& operator<< (std::ostream& out, Number& num) {
// 	if (num.getDen() == 1)
// 		out << num.getNum();
// 	else if(num.getNum() < num.getDen()) 
// 		out << num.getNum() << "/" << num.getDen();
// 	else
// 		out << num.getNum() / num.getDen() << "'" 
// 		<< num.getNum() - num.getNum() / num.getDen() * num.getNum()
// 		<< "/" << num.getDen();
// 	return out;
// }
//
// std::ostream& operator<< (std::ostream& out, Operator& o) {
// 	if(o.func == Number::Add) out << "+";
// 	else if(o.func == Number::Minus) out << "-";
// 	else if(o.func == Number::Multiply) out << "*";
// 	else if(o.func == Number::Divide) out << "/";
// 	return out;
// }