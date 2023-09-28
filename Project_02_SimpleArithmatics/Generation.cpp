#include "Generation.h"
#include <string>
#include <fstream>


std::vector<int> Generation::NumGeneration(int numLimit)
{
	std::vector<int> List;
	// 创建伪随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(0, numLimit);

	// 生成随机自然数
	for (int i = 0; i < 4; i++)
	{
		int randomNaturalNumber = dist(gen);
		List.push_back(randomNaturalNumber);
	}
	return List;
}

std::vector<char> Generation::OperatorGeneration()
{
	std::vector<char> List;
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(1, 3);

	// 生成运算符个数
	int operatorNum = dist(gen);
	for (int i = 0; i < operatorNum; i++)
	{
		std::uniform_int_distribution<int> dist(1, 4);
		int randomOperatorNumber = dist(gen);
		char opera;
		switch (randomOperatorNumber)
		{
		case 1: opera = '+'; break;
		case 2: opera = '-'; break;
		case 3: opera = '*'; break;
		case 4: opera = '/'; break;
		default: break;
		}
		List.push_back(opera);
	}
	return List;
}

std::string Generation::Combination(std::vector<int>& numList, std::vector<char>& operaList)
{
	std::string result;

	for (int i = 0; i < numList.size(); ++i) {
		result += std::to_string(numList[i]); // 将数字转换为字符串并追加到结果字符串中

		if (i < operaList.size()) {
			result += operaList[i]; // 如果还有运算符，插入运算符
		}
		if (i == operaList.size())
		{
			break;
		}
	}
	return result;
}

void Generation::IOsystem()
{
	Arithmetics A;
	std::ofstream outFile("exercisefile.txt");
	std::ofstream outFile_answer("Answer.txt");
	if (!outFile) {
		std::cerr << "无法打开输出文件." << std::endl;
		return;
	}
	if (!outFile_answer) {
		std::cerr << "无法打开输出文件." << std::endl;
		return;
	}
	for (int i = 0; i < request; i++)
	{
		
		std::vector<int>numList = NumGeneration(numLimit);
		std::vector<char>operaList = OperatorGeneration();
		std::string expression = Combination(numList, operaList);
		if (expression.size()>3)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(0, 1);

			int isParentheses = dist(gen); // 随机生成 0 或 1
			if (isParentheses == 1)
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(0, 3);
				int parenthesesPosition = dist(gen) * 2;
				while (parenthesesPosition > expression.size() - 2)
				{
					parenthesesPosition = parenthesesPosition - 2;
				}
				expression.insert(parenthesesPosition,1, '(');
				expression.insert(parenthesesPosition + 4, 1, ')');

			}
		}
		A.string_without_space_to_equation(expression);
		std::string res = A.get_result().to_string();
		if (A.get_result().numerator > 729||A.get_result().denominator>729) {
			i--;
			A.clear();
			continue;
		}
		outFile << i + 1 << ". " << expression << "\n";
		outFile_answer << i + 1 << ". " << res << "\n";
		A.clear();
	}
	outFile.close();
	outFile_answer.close();
}

void Generation::Compare(void)
{
	std::vector<int> wrongNum;
	std::vector<int> trueNum;

	std::ifstream file1("answerfile.txt");
	std::ifstream file2("Answer.txt");

	if (!file1.is_open() || !file2.is_open()) {
		std::cerr << "Failed to open one or both files." << std::endl;
		return;
	}

	std::string line1, line2;
	int lineNumber = 1;
	while (std::getline(file1, line1) && std::getline(file2, line2)) {
		if (line1 != line2) {
			wrongNum.emplace_back(lineNumber);
		}
		trueNum.emplace_back(lineNumber);
		lineNumber++;
	}

	if (file1.eof() && file2.eof()) {
		std::cout << "Both files are identical." << std::endl;
	}
	else if (!file1.eof()) {
		std::cout << "每道题只对应一个答案，请检查是否重复回答或未按照格式回答" << std::endl;
	}
	else {
		std::cout << "未完整回答所有题目或未按照格式回答" << std::endl;
	}
	file1.close();
	file2.close();
	std::ofstream grade("Grade.txt");
	if (!grade.is_open()) {
		std::cerr << "Failed to open files." << std::endl;
	}
	std::string commaSeparated;
	for (int num : trueNum) {
		commaSeparated += std::to_string(num) + ", ";
	}
	
	if (!commaSeparated.empty()) {
		commaSeparated = commaSeparated.substr(0, commaSeparated.length() - 2);
	}
	grade << "Correct:" << trueNum.size() << "( "<<commaSeparated<<")"<<"\n";
	commaSeparated="";
	for (int num : wrongNum) {
		commaSeparated += std::to_string(num) + ", ";
	}
	if (!commaSeparated.empty()) {
		commaSeparated = commaSeparated.substr(0, commaSeparated.length() - 2);
	}
	grade << "Wrong:" << wrongNum.size() << "( " << commaSeparated << ")" << "\n";
}



