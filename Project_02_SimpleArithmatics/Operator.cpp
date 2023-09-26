#include "Operator.h"

operatorFunc Operator::operator_func[6] = {
    Number::add, Number::minus, Number::multiply, Number::divide, nullptr, nullptr
};
unsigned char Operator::operator_priority[6] = {0, 0, 1, 1, 2, 2};
char Operator::operator_char[6] = {'+', '-', '*', '/', '(', ')'};


Operator::Operator(const char& operator_char)
{
    switch (operator_char)
    {
    case '+': type = e_operator_type::ADD; break;
    case '-': type = e_operator_type::Minus; break;
    case '*': type = e_operator_type::Multiply; break;
    case '/': type = e_operator_type::Divide; break;
    case '(': type = e_operator_type::LeftBrace; break;
    case ')': type = e_operator_type::RightBrace; break;
    default: type = e_operator_type::ERROR;break;
    }
}

Number Operator::func(const Number& A, const Number& B) const
{
    Number result = operator_func[type](A, B);
#if CALCULATE_DEBUG
    std::cout << A.to_string() << " " << operator_char[type] << " " << B.to_string()
                << " = " << result.to_string() << std::endl;
#endif
    return result;
}

std::string Operator::to_string() const
{
    return std::string(1,operator_char[type]);
}


std::ostream& operator<< (std::ostream& out, Operator& o) {
    out << Operator::operator_char[o.type];
    return out;
}

bool Operator::is_operator(const char& ch)
{
    for (char o : Operator::operator_char) {
        if (ch == o) return true;
    }
    return false;
}