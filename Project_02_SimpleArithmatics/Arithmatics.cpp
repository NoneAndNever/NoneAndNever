#include "Arithmatics.h"

#include <stack>

void Arithmatics::string_to_equation(std::string str)
{
    unsigned int state = 0; // 0 for space, 1 for number, 2 for operator
    unsigned int i = 0;
    unsigned int j = i;
    for (; i < str.length(); i++) {
        // when to add element
        // when digit ends (state == 1 but not digit)
        // when operator ends (state == 2)
        if (state == 1 && !isdigit(str[i]) || state == 2) {
            switch (state)
            {
            case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
            case 2: operators.emplace_back(str[i-1]); break;
            }

            //// prevent situation like "2/7"
            //if (Operator::is_operator(str[i])) 
            //{
            //    operators.emplace_back(str[i]);
            //    ++i;
            //}
            state = 0;
        }
        while (str[i] == ' ') i++;
        if (!state) {
            if (isdigit(str[i])){
                state = 1;
                j = i;
            }
            else if(Operator::is_operator(str[i])){
                state = 2;
            }
        }
    }
    switch (state)
    {
    case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
    case 2: operators.emplace_back(str[i-1]); break;
    }
}

void Arithmatics::string_with_space_to_equation(std::string str)
{
	int state = 0; // 0 for space, 1 for number, 2 for operator, 3 for fraction
	int i = 0;
    int j = i;
    int k = i;
	while (str[i] == ' ') i++;
	for (; i < str.length(); i++) {

        if (str[i] == ' ' && state) {
            switch (state)
            {
            case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
            case 2: operators.emplace_back(str[i-1]);break;
            case 3: nums.emplace_back(std::stoi(str.substr(j, k - j)), std::stoi(str.substr(k + 1, i - k - 1))); break;
            default:
                break;
            }
            state = 0;
        }
        while (str[i] == ' ') i++;
        if (!state) {
            if (isdigit(str[i])){
                state = 1;
                j = i;
                continue;
            }
            else if(Operator::is_operator(str[i])){
                state = 2;
            }
        }
        else if (state == 1 && str[i] == '/'){
            state = 3;
            k = i;
        }
	}
    switch (state)
    {
	    case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
	    case 2: operators.emplace_back(str[i-1]); break;
	    case 3: nums.emplace_back(std::stoi(str.substr(j, k - j)), std::stoi(str.substr(k + 1, i - k - 1))); break;
    }
}

void Arithmatics::string_without_space_to_equation(std::string str)
{
    int i = 0;
    int j = i;
    for (; i < str.length(); i++) {
        if (isdigit(str[i])) continue;
        if(j != i) nums.emplace_back(std::stoi(str.substr(j, i - j)));
        else std::cerr<<"Wrong Input.";
        operators.emplace_back(str[i]);
        j = i + 1;
    }
}

std::string Arithmatics::equation_to_string() const
{
    std::string s;
    auto it_num = nums.begin();
    auto it_opr = operators.begin();
    while (true) {
        if(it_num != nums.end())
        {
            s += (*it_num).to_string();
            ++it_num;
        }
        else break;
        
        while (it_opr != operators.end() && it_opr->get_type() == RightBrace)
        {
            s += (*it_opr).to_string();
            ++it_opr;
        }
        if(it_opr != operators.end())
        {
            s += (*it_opr).to_string();
            ++it_opr;
            while (it_opr != operators.end() && it_opr->get_type() == LeftBrace)
            {
                s += (*it_opr).to_string();
                ++it_opr;
            }
        }
        else break;
    }
    return s;
}

Number Arithmatics::get_result()
{
    if(result.is_valid()) return result;
    result = calculate();
    return result;
}

Number Arithmatics::calculate()
{
    if(nums.empty()) return Number{0};
    std::vector<Number>::iterator it_num = nums.begin();
    auto it_opr = operators.begin();
    std::stack<Number> num_stack;
    std::stack<Operator> opr_stack;
    
    while(it_num != nums.end())
    {
        if(it_opr->get_type() == LeftBrace)
        {
            num_stack.push(calculate_in_brace(it_num, ++it_opr));
        }
        if(it_num == nums.end()) break;
        num_stack.push(*it_num);
        ++it_num;

        if(it_opr == operators.end()) break;

        // if the operator stack is not empty and next operator's priority is less equal than previous operator's
        while(!opr_stack.empty() && it_opr->get_priority() <= opr_stack.top().get_priority()) 
        {
            Number& b = num_stack.top();
            num_stack.pop();
            Number& a = num_stack.top();
            num_stack.pop();
                
            num_stack.push(opr_stack.top().func(a, b));
            opr_stack.pop();
        }

        opr_stack.push(*it_opr);
        ++it_opr;
    }
    if(num_stack.empty())
    {
        std::cerr << "ERROR : Empty result";
        return Number{0, 0};
    }
    while(!opr_stack.empty())
    {
        Number& b = num_stack.top();
        num_stack.pop();
        Number& a = num_stack.top();
        num_stack.pop();
                
        num_stack.push(opr_stack.top().func(a, b));
        opr_stack.pop();
    }
    return num_stack.top();
}

Number Arithmatics::calculate_in_brace(std::vector<Number>::iterator& it_num,
                                       std::vector<Operator>::iterator& it_opr)
{
    std::stack<Number> num_stack;
    std::stack<Operator> opr_stack;
    while(true)
    {
        if(it_opr->get_type() == LeftBrace)
        {
            num_stack.push(calculate_in_brace(it_num, ++it_opr));
        }
        
        num_stack.push(*it_num);
        ++it_num;

        if(it_opr == operators.end() || it_opr->get_type() == e_operator_type::RightBrace) break;
        

        while(!opr_stack.empty() && it_opr->get_priority() <= opr_stack.top().get_priority() && num_stack.size() >= 2)//并且下一运算符的优先级低于当前,则处理前段计算
        {
            Number& b = num_stack.top();
            num_stack.pop();
            Number& a = num_stack.top();
            num_stack.pop();
            
            num_stack.push(opr_stack.top().func(a, b));
            opr_stack.pop();
        }
        
        opr_stack.push(*it_opr);
        ++it_opr;
    }
    if(it_opr == operators.end())
    {
        std::cerr << "ERROR : Incomplete braces.";
        if(num_stack.empty())
        {
            std::cerr << "ERROR : Empty braces.";
            return Number{1, 0};
        }
        return num_stack.top(); 
    }
    else
    {
        ++it_opr; // skip if it was right brace
    }
    
    if(num_stack.empty())
    {
        std::cerr << "ERROR : Empty result";
        return Number{0, 0};
    }

    while(!opr_stack.empty())
    {
        Number& b = num_stack.top();
        num_stack.pop();
        Number& a = num_stack.top();
        num_stack.pop();
                
        num_stack.push(opr_stack.top().func(a, b));
        opr_stack.pop();
    }
    
    return num_stack.top();
}


