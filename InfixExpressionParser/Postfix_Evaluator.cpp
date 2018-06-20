#include "Postfix_Evaluator.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cctype>

const std::string Postfix_Evaluator::OPERATORS = "!+-^*/%><=&|";

int Postfix_Evaluator::eval(const std::string & expression)
{
	while (!operand_stack.empty())
		operand_stack.pop();

	std::istringstream iss(expression);
	std::vector<std::string> tokenized;
	for (std::string s; iss >> s;) {
		tokenized.push_back(s);
	}
	for (std::vector<std::string>::const_iterator i = tokenized.begin(); i != tokenized.end(); ++i)
		std::cout << *i << std::endl;
	return 0;
	//char next_char;
	//while (tokens >> next_char) {
	//	if (isdigit(next_char)) {
	//		tokens.putback(next_char);
	//		int value;
	//		tokens >> value;
	//		operand_stack.push(value);
	//	}
	//	else if (is_operator(next_char)) {
	//		int result = eval_op(next_char);
	//		operand_stack.push(result);
	//	}
	//	else {
	//		throw Syntax_Error("Invalid character encountered");
	//	}
	//}
	//if (!operand_stack.empty()) {
	//	int answer = operand_stack.top();
	//	operand_stack.pop();
	//	if (operand_stack.empty()) {
	//		return answer;
	//	}
	//	else {
	//		throw Syntax_Error("Stack should be empty");
	//	}
	//}
	//else {
	//	throw Syntax_Error("Stack is empty");
	//}
}

int Postfix_Evaluator::eval_op(char op)
{
	return 0;
}

bool Postfix_Evaluator::is_operator(char ch) const
{
	return false;
}
