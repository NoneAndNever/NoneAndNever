#include "Arithmetics.h"
#include "Generation.h"
#include <sstream>
#include <iostream>

int main() {

	// 	Arithmetics arithmetics;
	// 	arithmetics.string_to_equation("21 + ((25/3) * 6 - 14 )");
	// 	//arithmatics.StringWithoutSpace2Equation("1+(2/3*7-8)");
	// 	std::string s = arithmetics.equation_to_string();
	// 	std::string res = arithmetics.get_result().to_string();
	// 	system("pause");
	// 	return 0;
	
	std::cout << "请输入需要生成的题目个数" << std::endl;
	std::string input;
	int request;
	while (true) {
		std::getline(std::cin, input);
		// 使用字符串流尝试将输入转换为整数
		std::istringstream stream(input);
		if (stream >> request) {
			// 输入是整数，退出循环
			break;
		}
		else {
			// 输入不是整数，显示错误消息并继续循环
			std::cout << "错误：请输入一个有效的整数。" << std::endl;
		}

	}
	std::cout << "请输入题中数值的最大值" << std::endl;
	std::string input_max;
	int numLimit;
	while (true) {
		std::getline(std::cin, input_max);
		// 使用字符串流尝试将输入转换为整数
		std::istringstream stream(input_max);
		if (stream >> numLimit) {
			// 输入是整数，退出循环
			break;
		}
		else {
			// 输入不是整数，显示错误消息并继续循环
			std::cout << "错误：请输入一个有效的整数。" << std::endl;
		}
	}
	Generation G(numLimit, request);
	G.IOsystem();
	std::cout << "是否已完成题目并将答案输入answerfile.txt"<<std::endl;
	input="";
	int test;
	while (true) {
		std::getline(std::cin, input);
		// 使用字符串流尝试将输入转换为整数
		std::istringstream stream(input);
		if (stream >> test) {
			if(test==0||test==1)
			break;
		}
		else {
			// 输入不是0或1，显示错误消息并继续循环
			std::cout << "错误：请输入0或1。" << std::endl;
		}
	}
	if (test == 0)
		return 0;
	else
		std::cout << "你的成绩已在Grade.txt显示";
	G.Compare();
	std::cout << "Press Enter to continue...";
	std::cin.get();  // 等待用户按下 Enter 键
	return 0;
}