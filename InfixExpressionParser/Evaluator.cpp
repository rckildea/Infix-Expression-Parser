#include "Evaluator.h"


int Evaluator::evaluate(const std::string & expression) {
	original_expression = expression;

	while (!operand_stack.empty()) {
		operand_stack.pop();
	}

	std::istringstream iss(expression);
	std::string token;
	std::string temp;
	int pos = 0;

	while (iss >> token) {
		if (token[0] == '-') {
			for (int i = 0; i < token.length(); ++i) {
				if (isdigit(token[i])) {
					if (i % 2 == 0) {
						operand_stack.push(stoi(token.substr(i)));
					}
					else {
						operand_stack.push(-1 * stoi(token.substr(i)));
					}
				}
			}
		}
		else if (isdigit(token[0])) {
			operand_stack.push(stoi(token));
		}
		else {
			if (token == "(" || token == "[" || token == "{" || operator_stack.empty()) {
				operator_stack.push(token);
			}
			else {
				if (token == ")" || token == "]" || token == "}") {
					while (operator_stack.top() != get_matching_parentheses(token)) {
						char op = operator_stack.top()[0];
						operator_stack.pop();
						int rhs = operand_stack.top();
						operand_stack.pop();
						calculate(rhs, op);
					}
					operator_stack.pop();
				}
				else if (higher_precedence(token, operator_stack.top())) {
					operator_stack.push(token);
				}
				else {
					temp = token;
					while (!operator_stack.empty()) {
						char op = operator_stack.top()[0];
						operator_stack.pop();
						int rhs = operand_stack.top();
						operand_stack.pop();
						calculate(rhs, op);
					}
					operator_stack.push(temp);
				}
			}
		}
	}

	while (!operator_stack.empty()) {
		char op = operator_stack.top()[0];
		operator_stack.pop();
		int rhs = operand_stack.top();
		operand_stack.pop();
		calculate(rhs, op);
	}

	return operand_stack.top();
}

void Evaluator::calculate(int rhs, char op) {
	if (is_unary(op)) {
		switch(op) {
			case '!': operand_stack.push(!rhs); break;
			case '~': operand_stack.push(++rhs); break;
			case '_': operand_stack.push(--rhs); break;
		}
	}
	else {
		int lhs = operand_stack.top();
		operand_stack.pop();
		switch (op) {
			case '^': operand_stack.push(int(pow(lhs, rhs))); break;
			case '*': operand_stack.push(lhs * rhs); break;
			case '/': 
				if (rhs == 0) {
					int num_divisions = 1;
					while (!operator_stack.empty()) {
						if (operator_stack.top()[0] == '/') {
							++num_divisions;
						}
					}
					std::cout << "Error: Division by zero" << std::endl;
				}
				else {
					operand_stack.push(lhs / rhs);
				}
				break;
			case '%': operand_stack.push(lhs % rhs); break;
			case '+': operand_stack.push(lhs + rhs); break;
			case 'm': operand_stack.push(lhs - rhs); break;
			case '>': operand_stack.push(lhs > rhs); break;
			case '@': operand_stack.push(lhs >= rhs); break;
			case '<': operand_stack.push(lhs < rhs); break;
			case '#': operand_stack.push(lhs <= rhs); break;
			case '=': operand_stack.push(lhs == rhs); break;
			case '$': operand_stack.push(lhs != rhs); break;
			case '&': operand_stack.push(lhs && rhs); break;
			case '|': operand_stack.push(lhs || rhs); break;
		}
	}
}

bool Evaluator::higher_precedence(std::string current, std::string top) {
	const std::string OPERATORS = "!~_-^*/%+m>@<#=$&|()[]{}";
	const int PRECEDENCE[] = { 8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1, -1, -1, -1, -1, -1, -1 };

	if (PRECEDENCE[OPERATORS.find(current)] >= PRECEDENCE[OPERATORS.find(top)]) {
		return true;
	}

	return false;
}

bool Evaluator::is_unary(char op) {
	if (op == '!' || op == '~' || op == '_') {
		return true;
	}

	return false;
}

std::string Evaluator::get_matching_parentheses(std::string p) {
	if (p == ")") {
		return "(";
	}
	else if (p == "]") {
		return "[";
	}
	else {
		return "{";
	}
}
