#pragma once
#include"Number.h"

typedef Number(*operatorFunc)(const Number&, const Number&);

enum e_operator_type
{
	ADD,
	Minus,
	Multiply,
	Divide,
	LeftBrace,
	RightBrace,
	ERROR
};

class Operator {
private:
	// READONLY VARIABLES
	// default value :
	// Function:		priority	char
	// Number::add,			0		 +
	// Number::minus,		0		 -
	// Number::multiply,	1		 *
	// Number::divide,		1		 /
	// nullptr,				2		 (
	// nullptr				2		 )	
	static operatorFunc operator_func[6];
	static unsigned char operator_priority[6];
	static char operator_char[6];

	e_operator_type type = e_operator_type::ERROR;
public:
	Operator(const char& operator_char);

	static bool is_operator(const char& ch);

	// call the corresponding function of the operator
	Number func(const Number& A, const Number& B) const;

	char get_char() const { return operator_char[type]; }
	unsigned char get_priority() const { return operator_priority[type]; }
	e_operator_type get_type() const { return type; }

	std::string to_string() const;

	//operatorFunc& operator*() { return operator_func[type]; }
	//operatorFunc* operator->() { return &operator_func[type]; }
	friend std::ostream& operator<< (std::ostream& out, Operator& o);

};

