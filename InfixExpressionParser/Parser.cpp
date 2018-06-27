#include "Parser.h"

Parser::Parser() {
}

std::string Parser::Parse(std::string expression) {

	std::string current; // Token that was just read in
	std::string next_item; // Formatted string to add to clean_expression
	std::string clean_expression = ""; // Properly formatted expression
	std::istringstream iss(expression);
	int pos = 0;

	bool previous_was_digit = false;
	bool previous_was_binary_operator = false;

	if (expression[0] == ')' || expression[0] == ']' || expression[0] == '}') {
		std::cout << "Error: Expression can't start with a closing parentheses @ pos: 0 char: " << expression[0] << std::endl;
	}

	if (isoperator(expression[0])) {
		if (expression[0] != '!' && expression[0] != '+' && expression[0] != '-' && expression[0] != '(' && expression[0] != '[' && expression[0] != '{') {
			std::cout << "Error: Expression can't start with a binary operator @ pos: 0 char: " << expression[0] << std::endl;
		}
		if (&expression[1] != nullptr && expression[0] == '+' && expression[1] != '+') {
			std::cout << "Error: Expression can't start with a binary operator @ pos: 0 char: " << expression[0] << std::endl;
		}
	}

	while (iss >> current) {

		for (int i = 0; i < current.size(); ++i) {
			next_item = "";

			if (isdigit(current[i])) {
				if (previous_was_digit) { // Two operands in a row
					std::cout << "Error: Two operands in a row @ pos: " << pos << " char: " << current[i] << std::endl;
				}
				previous_was_digit = true; // Remembers the previous run had a number
				for (std::string::iterator iter = current.begin() + i; iter != current.end(); ++iter) { // Now that a number has been found, keep reading the token until the number ends
					if (isdigit(*iter)) {
						next_item += *iter;
						++pos;
						++i;
					}
					else {
						--i;
						--pos;
						break;
					}
				}
				previous_was_binary_operator = false;
			}

			else if (isoperator(current[i])) {
				if (current[i] == '-' && current[i + 1] != '-') {
					if (previous_was_digit) {
						next_item = "m";
					}
					else {
						next_item = "-";
					}
				}

				else if (isoperator(current[i + 1])) {
					if (current[i] == '-' && current[i + 1] == '-') {
						if (previous_was_digit) {
							if (isdigit(current[i + 2])) {
								next_item = "m -";
							}
							else {
								next_item = "_";
							}
						}
						else {
							next_item = "--";
						}
					}
					else {
						next_item = process_double_operators(current[i], current[i + 1]);
						if (next_item[0] == '?') {
							next_item = std::string() + current[i] + " " + current[i + 1];
						}
					}
					++pos;
					++i;
				}
				else {
					next_item = current[i];
				}
				if (check_binary_operator(next_item[0])) {
					if (previous_was_binary_operator) {
						std::cout << "Error: Two binary operators in a row @ pos: " << pos << " char: " << current[i] << std::endl;
					}
					else {
						previous_was_binary_operator = true;
					}
				}
				previous_was_digit = false;
			}
			else { // Is not a digit and is not an operator
				std::cout << "Error: Invalid character @ pos: " << pos << " char: " << current[i] << std::endl;
			}

			if (next_item != "m -" && next_item != "-" && next_item != "--") {
				clean_expression += next_item + " ";
			}
			else {
				clean_expression += next_item;
			}
		}
		++pos;
	}

	return clean_expression;
}

bool Parser::isoperator(char ch) {
	const std::string OPERATORS = "!~_-^*/%+m>@<#=$&|()[]{}";

	for (std::string::const_iterator iter = OPERATORS.begin(); iter != OPERATORS.end(); ++iter) {
		if (ch == *iter) {
			return true;
		}
	}
	return false;
}

char Parser::process_double_operators(char first, char second) {
	if (first == '+' && second == '+') {
		return '~';
	}
	else if (first == '-' && second == '-') {
		return '-';
	}
	else if (first == '>' && second == '=') {
		return '@';
	}
	else if (first == '<' && second == '=') {
		return '#';
	}
	else if (first == '=' && second == '=') {
		return '=';
	}
	else if (first == '!' && second == '=') {
		return '$';
	}
	else if (first == '&' && second == '&') {
		return '&';
	}
	else if (first == '|' && second == '|') {
		return '|';
	}
	else {
		return '?';
	}
}

bool Parser::check_binary_operator(char op) {
	const std::string BINARY_OPERATORS = "^*/%+m>@<#=$&|";

	for (std::string::const_iterator iter = BINARY_OPERATORS.begin(); iter != BINARY_OPERATORS.end(); ++iter) {
		if (op == *iter) {
			return true;
		}
	}
	return false;
}
