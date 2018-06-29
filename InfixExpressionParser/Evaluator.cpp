#include "Evaluator.h"

/* Evaluates the parser-formatted user expression */
/** Takes an expression formatted by the parser and evaluates the expression
@param expression The parser-formatted expression
@return The result of the expression
*/
int Evaluator::evaluate(std::string & expression) {

	try {
		expression = Parser::Parse(expression);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	
	original_expression = expression; // Copy to find position of any errors

	while (!operand_stack.empty()) { // Ensure no operands on the stack
		operand_stack.pop();
	}

	std::istringstream iss(expression);
	std::string token; // Current token being analyzed
	std::string temp; // Stores lower precedence operator when one is met

	while (iss >> token) {
		if (isdigit(token[0])) { // Push numbers immediately
			operand_stack.push(stoi(token));
		}
		else {
			if (token == "(" || token == "[" || token == "{" || operator_stack.empty()) { // Push open parentheses immediately
				operator_stack.push(token);
			}
			else {
				if (token == ")" || token == "]" || token == "}") {
					while (operator_stack.top() != get_matching_parenthesis(token)) { // Evaluate & remove until matching parentheses found
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
					temp = token; // Save current operator to be added to the stack once cleared
					while (!operator_stack.empty() && operator_stack.top() != "("
						&& operator_stack.top() != "[" && operator_stack.top() != "{") {
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

	while (!operator_stack.empty()) { // Evaluate all remaining operators
		char op = operator_stack.top()[0];
		operator_stack.pop();
		int rhs = operand_stack.top();
		operand_stack.pop();
		calculate(rhs, op);
	}

	std::cout << "\n" << "ANSWER:\n" << operand_stack.top() << std::endl;
	return operand_stack.top();
}

/** Evaluates a sub-expression
@param rhs The right hand side of the expression
@param op The operator
@return The result of the sub-expression
*/
void Evaluator::calculate(int rhs, char op) {
	if (is_unary(op)) {
		switch(op) {
			case '!': operand_stack.push(!rhs); break;
			case '~': operand_stack.push(++rhs); break;
			case '_': operand_stack.push(--rhs); break;
			case '-': operand_stack.push(-rhs); break;
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
					divided_by_zero();
				}
				operand_stack.push(lhs / rhs);
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

/** Determines the precedence of operators
@param current The most recently read operator
@param top The operator on top of the stack
@return True (new operator is higher precedence) or false (old operator is higher precedence)
*/
bool Evaluator::higher_precedence(std::string current, std::string top) {
	const std::string OPERATORS = "!~_-^*/%+m>@<#=$&|()[]{}";
	const int PRECEDENCE[] = { 8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1, -1, -1, -1, -1, -1, -1 };

	if (PRECEDENCE[OPERATORS.find(current)] >= PRECEDENCE[OPERATORS.find(top)]) {
		return true;
	}

	return false;
}

/** Determines whether or not the currently analyzed operator is a unary operator
@param op The operator
@return True or false
*/
bool Evaluator::is_unary(char op) {
	if (op == '!' || op == '~' || op == '_' || op == '-') {
		return true;
	}

	return false;
}

/** Returns the matching open parenthesis for a closed parenthesis
@param p The closing parenthesis
@return The matching open parenthesis
*/
std::string Evaluator::get_matching_parenthesis(std::string p) {
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

/** Handles procedure when the equation tries to divide by zero
*/
void Evaluator::divided_by_zero() {
	int num_divisions = 1;
	int current = 0;
	int pos = 0;
	while (!operator_stack.empty()) {
		if (operator_stack.top()[0] == '/') { // Count the number of divisions to know where error ocurred
			++num_divisions;
		}
		operator_stack.pop();
	}
	for (std::string::iterator iter = original_expression.begin(); // Find position of error-causing division
		iter != original_expression.end(); ++iter) {
		if (*iter == '/') {
			++current;
			if (current == num_divisions) {
				pos = iter - original_expression.begin();
			}
		}
	}

	throw std::runtime_error(std::string() + "Error: Division by zero @ pos: " + std::to_string(pos));
}