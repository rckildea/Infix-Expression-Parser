#include <stack>
#include <string>
#include <sstream>
#include "Parser.h"
#include "Evaluator.h"

int main() {
	std::stack<char> operator_stack;
	std::stack<int> operand_stack;
	Evaluator e;

	std::string expression = "7 + 3 * (5 + 9 -4) / 3";

	std::string new_expression = Parser::Parse(expression);
	
	std::cout << new_expression << std::endl;

	int result = e.evaluate(new_expression);

	std::cout << "\n" << result << std::endl;

	return 0;
}