#include "Arithmatics.h"
#include "Number.h"

void Arithmatics::String2Equation(std::string str)
{
	int state = 0; // 0为空格，1为数字,2为符号,3为分数
	int i = 0;
    int j = i;
    int k = i;
	while (str[i] == ' ') i++;
	for (; i < str.length(); i++) {
        //如果遇到结束空格
        if (str[i] == ' ' && state) {
            switch (state)
            {
            case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
            case 2: break;
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
            else{
                switch (str[i])
                {
                case '+': operators.push_back(Number::Add); break;
                case '-': operators.push_back(Number::Minus); break;
                case '*': operators.push_back(Number::Multiply); break;
                case '/': operators.push_back(Number::Divide); break;
                default:
                    break;
                }
            }
        }
        else if (state == 1 && !isdigit(str[i])){
            state = 3;
            k = i;
        }
	}
    switch (state)
    {
	    case 1: nums.emplace_back(std::stoi(str.substr(j, i - j))); break;
	    case 3: nums.emplace_back(std::stoi(str.substr(j, k - j)), std::stoi(str.substr(k + 1, i - k - 1))); break;
    }
}

std::string Arithmatics::Equation2String() const
{
    std::string s;
    auto it_num = nums.begin();
    auto it_ope = operators.begin();
    while (true) {
        if(it_num != nums.end())
        {
            s += (*it_num).to_string();
            ++it_num;
        }
        else break;
        
        if(it_ope != operators.end())
        {
            s += (*it_ope).to_string();
            ++it_ope;
        }
        else break;
    }
    return s;
}
