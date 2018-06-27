#include "Parser.h"

Parser::Parser() {
}

std::string Parser::Parse(std::string expression) {

	std::string current;
	std::string next_item;
	std::string clean_expression = "";
	std::istringstream iss(expression);

	bool binary_operator_flag = false;

	if (expression[0] == ')' || expression[0] == ']' || expression[0] == '}') {
		std::cout << "Error: Expression can't start with a closing parentheses @ char: 0";
	}

	if (isoperator(expression[0])) {
		if (expression[0] != '!' && expression[0] != '+' && expression[0] != '-' && expression[0] != '(' && expression[0] != '[' && expression[0] != '{') {
			std::cout << "Error: Expression can't start with a binary operator @ char: 0";
		}
		if (&expression[1] != nullptr && expression[0] == '+' && expression[1] != '+') {
			std::cout << "Error: Expression can't start with a binary operator @ char: 555";
		}
	}

	while (iss >> current) {

		for (int i = 0; i < current.size(); ++i) {
			next_item = "";

			if (isdigit(current[i])) {
				binary_operator_flag = true; // Remembers the previous run had a number
				for (std::string::iterator iter = current.begin() + i; iter != current.end(); ++iter) {
					if (isdigit(*iter)) {
						next_item += *iter;
						i++;
					}
					else {
						i--;
						break;
					}
				}
			}

			else if (isoperator(current[i])) {
				if (current[i] == '-') {
					if (current[i + 1] != '-' && binary_operator_flag) {
						next_item = "m";
					}
					else {
						next_item = "-";
					}
				}

				else if (isoperator(current[i + 1])) {
					if (current[i] == '-' && current[i + 1] == '-' && binary_operator_flag) {
						if (isdigit(current[i + 2])) {
							next_item = "m -";
						}
						else {
							next_item = "_";
						}
					}
					else {
						next_item = process_double_operators(current[i], current[i + 1]);
						if (next_item[0] == '?') {
							next_item = std::string() + current[i] + " " + current[i + 1];
						}
					}
					++i;
				}
				else {
					next_item = current[i];
				}

				binary_operator_flag = false;
			}
			else {
				std::cout << "Error at position " + i << std::endl;
			}

			if (next_item != "m -") {
				clean_expression += next_item + " ";
			}
			else {
				clean_expression += next_item;
			}
		}
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