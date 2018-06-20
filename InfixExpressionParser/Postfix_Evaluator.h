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

	int eval_op(char op);
	bool is_operator(char ch) const;
};

