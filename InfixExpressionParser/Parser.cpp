#include "Parser.h"

/* Takes a user expression and formats it to be easily analyzed by the evaluator */

/** Converts user expression into an expression easily interpretable by the evaluator
@param expression The user expression
@return The formatted expression
*/
std::string Parser::Parse(std::string expression) {

	std::string current; // Token that was just read in
	std::string next_item; // Formatted string to add to clean_expression
	std::string clean_expression = ""; // Properly formatted expression
	std::istringstream iss(expression);
	int pos = 0; // For notifying user of the position where an error occurs

	bool previous_was_digit = false;
	bool previous_was_binary_operator = false;

	while (iss >> current) {

		for (int i = 0; i < current.size(); ++i) {
			next_item = ""; // Clear the string to append to the clean expression

			if (isdigit(current[i])) {
				for (std::string::iterator iter = current.begin() + i; iter != current.end(); ++iter) { // Now that a number has been found, keep reading the token until the number ends
					if (isdigit(*iter)) {
						next_item += *iter;
						++pos;
						++i;
					}
					else { // Will read one item to far; corrected here
						--i;
						--pos;
						break;
					}
				}
				previous_was_digit = true;
				previous_was_binary_operator = false;
			}

			else if (isoperator(current[i])) {
				if (current[i] == '-') {
					next_item = handle_minus(current, i, previous_was_digit, previous_was_binary_operator);
					if (next_item[0] == '_' || next_item.length() > 1) {
						++i;
						++pos;
					}
				}
				else if (isoperator(current[i + 1])) { // Two operators in a row
					next_item = process_double_operators(current[i], current[i + 1]);
					if (next_item[0] == '?') { // No suitable 2 character operator was found; must be two separate operators
						next_item = std::string() + current[i] + " " + current[i + 1];
					}
					++pos;
					++i;
				}
				else {
					next_item = current[i]; // Just a standard, single character operator
				}

				if (next_item[0] != ')' && next_item[0] != ']' && next_item[0] != '}') {
					previous_was_digit = false;
				}

				pos += 2; // One for the operator, one for the space
			}
			else { // Is not a digit and is not an operator
				throw std::runtime_error(std::string() + "Error: Invalid character @ pos: " + std::to_string(pos) + " char: " + current[i]);
			}

			if (is_binary_operator(next_item[0])) {
				previous_was_binary_operator = true;
			}
			

			clean_expression += next_item + " ";
		}
	}

	std::cout << "Formatted expression:\n" << clean_expression << std::endl;
	check_final_expression(clean_expression);

	return clean_expression;
}

/** Verifies a character is an operator
@param ch The character meant to represent an operator
@return True or false
*/
bool Parser::isoperator(char ch) {
	const std::string OPERATORS = "!-^*/%+><=&|()[]{}";

	for (std::string::const_iterator iter = OPERATORS.begin(); iter != OPERATORS.end(); ++iter) {
		if (ch == *iter) {
			return true;
		}
	}
	return false;
}

/** Determines whether or not the currently analyzed operator is a binary operator
@param char The operator
@return True or false
*/
bool Parser::is_binary_operator(char op) {
	const std::string BINARY_OPERATORS = "^*/%+m>@<#=$&|";

	for (std::string::const_iterator iter = BINARY_OPERATORS.begin(); iter != BINARY_OPERATORS.end(); ++iter) {
		if (op == *iter) {
			return true;
		}
	}
	return false;
}

/** Verifies a character is a parenthesis
@param ch The character meant to represent a parenthesis
@return True or false
*/
bool Parser::isparenthesis(char ch) {
	const std::string PARENTHESES = "()[]{}";

	for (std::string::const_iterator iter = PARENTHESES.begin(); iter != PARENTHESES.end(); ++iter) {
		if (ch == *iter) {
			return true;
		}
	}
	return false;
}

/** Attempts to convert two detected one-char operators into a one-char operator representing their union
@param char first The first char read in
@param char second The second char read in
@return The representative char (if match found), '?' (if no match found)
*/
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

/** Negative, minus, and decrement all use '-'.  This function interprets the equation
@param string token The most recently read token
@param int i The current index of the token
@param bool previous_was_digit True if the previous character was a digit
@param bool previous_was_binary_operator True if the previous character was a binary operator
@return The interpreted form of '-' or '--'
*/
std::string Parser::handle_minus(std::string token, int i, bool previous_was_digit, bool previous_was_binary_operator) {

	std::string next_item = "";
	if (token[i] == '-' && token[i + 1] != '-') { // Must be either a minus or a negative
		if (previous_was_digit) {
			next_item = "m"; // 'm' represents when '-' means "minus"
		}
		else {
			next_item = "-"; // '-' represents when '-' means "negative"
		}
	}
	else { // Two negatives in a row
		if (isdigit(token[i+2]) && !previous_was_digit || i == 0) {
				next_item = "_";
		}
		else if (previous_was_binary_operator) {
			next_item = "--";
		}
		else { // Previous was a digit
			next_item = "m -";
		}
	}
	return next_item;
}

/** Checks for errors in the formatted expression
@param string expression The formatted expression
*/
void Parser::check_final_expression(std::string expression) {
	// use a vector, tokenize the strings, iterate through vector
	std::istringstream iss(expression);
	std::vector<std::string> tokens;
	std::string token;
	while (iss >> token) {
		tokens.push_back(token);
	}

	if (tokens[0] == ")" || tokens[0] == "]" || tokens[0] == "}") {
		throw std::runtime_error(std::string() + "Error: Expression can't start with a closing parentheses @ pos: 0 char: " + tokens[0]);
	}

	if (is_binary_operator(tokens[0][0])) {
			throw std::runtime_error(std::string() + "Error: Expression can't start with a binary operator @ pos: 0 char: " + tokens[0]);
	}

	for (std::vector<std::string>::iterator iter = tokens.begin(); (iter+1) != tokens.end(); ++iter) {
		if (isdigit(iter[0][0])) {
			if (isdigit((iter + 1)[0][0])) {
				throw std::runtime_error(std::string() + "Error: Two operands in a row @ pos: " + std::to_string((iter - tokens.begin()) * 2) + " char: " + *iter);
			}
		}
		else if (is_binary_operator(iter[0][0])) {
			if (is_binary_operator((iter + 1)[0][0])) {
				throw std::runtime_error(std::string() + "Error: Two binary operators in a row @ pos: " + std::to_string((iter - tokens.begin()) * 2) + " char: " + *iter);
			}
		}
		else {
			if (is_binary_operator((iter + 1)[0][0]) && !isparenthesis(iter[0][0])) {
				throw std::runtime_error(std::string() + "Error: A unary operator can not be followed by a binary operator @ pos: " + std::to_string((iter - tokens.begin()) * 2) + " char: " + *iter);
			}
		}
	}
}
