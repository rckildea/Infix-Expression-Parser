#pragma once
#include <string>
#include "Syntax_Error.h"
#include "Stack.h"

class Postfix_Evaluator
{
public:
	int eval(const std::string& expression);
private:
	static const std::string OPERATORS;
	Stack<int> operand_stack;

	bool is_unary(std::string oper);
	int eval_op(std::string oper, bool unary);
	int get_operand();
};

