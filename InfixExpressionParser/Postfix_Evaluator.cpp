#include "Postfix_Evaluator.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <math.h>

const std::string Postfix_Evaluator::OPERATORS = "!+-^*/%><=&|";

int Postfix_Evaluator::eval(const std::string & expression)
{
	while (!operand_stack.empty())
		operand_stack.pop();

	std::istringstream iss(expression);
	std::vector<std::string> tokenized;
	std::string temp;
	while (iss >> temp) {
		tokenized.push_back(temp);
	}

	for (std::vector<std::string>::iterator i = tokenized.begin(); i != tokenized.end(); ++i) {
		if (isdigit((*i)[0])) {
			operand_stack.push(std::stoi(*i));
		}
		else { // Currently, "is_operator" is removed because this check is already performed in Infix_To_Postfix
			int result = eval_op(*i, is_unary(*i));
			operand_stack.push(result);
		}
	}
		

	if (!operand_stack.empty()) {
		int answer = operand_stack.top();
		operand_stack.pop();
		if (operand_stack.empty()) {
			return answer;
		}
		else {
			throw Syntax_Error("Stack should be empty");
		}
	}
	else {
		throw Syntax_Error("Stack is empty");
	}
}

bool Postfix_Evaluator::is_unary(std::string oper)
{
	if (oper == "!" || oper == "++" || oper == "--" || oper == "n") {
		return true;
	}

	return false;

}

int Postfix_Evaluator::eval_op(std::string oper, bool unary)
{
	int result = 0;

	if (unary) {
		int rhs = get_operand();
		if (oper == "!") return !rhs;
		if (oper == "++") return ++rhs;
		if (oper == "--") return --rhs;
		if (oper == "n") return -rhs;
	}
	else {
		int rhs = get_operand();
		int lhs = get_operand();
		if (oper == "^") return pow(lhs, rhs);
		if (oper == "*") return lhs * rhs;
		if (oper == "/") return lhs / rhs;
		if (oper == "%") return lhs % rhs;
		if (oper == "+") return lhs + rhs;
		if (oper == "-") return lhs - rhs;
		if (oper == ">") return lhs > rhs;
		if (oper == ">=") return lhs >= rhs;
		if (oper == "<") return lhs < rhs;
		if (oper == "<=") return lhs <= rhs;
		if (oper == "==") return lhs == rhs;
		if (oper == "!=") return lhs != rhs;
		if (oper == "&&") return (lhs && rhs);
		if (oper == "||") return (lhs || rhs);
	}

	return result;
}

int Postfix_Evaluator::get_operand()
{
	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
	int r_val = operand_stack.top();
	operand_stack.pop();
	return r_val;
}
