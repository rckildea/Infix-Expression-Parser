#include <cctype>
#include <algorithm>
#include <iostream> // remove later
#include <vector>
#include "Infix_To_Postfix.h"
#include "Syntax_Error.h"

/*
Symbols for two-character/other operators:
~: prefix increment
_: prefix decrement
$: negative
@: greater than or equal to
#: lesser than or equal to
d: equality
n: inequality
&: logical and
|: logical or
*/
const std::string Infix_To_Postfix::OPERATORS = "!~_n^*/%+->@<#=$&|()[]{}";
const std::string Infix_To_Postfix::SPECIAL_OPERATORS = "~_n@#=$&|";
const int Infix_To_Postfix::PRECEDENCE[] = { 8, 8, 8, 8, 7, 6, 6, 6, 5, 5, 4, 4, 4, 4, 3, 3, 2, 1, -1, -1, -1, -1, -1, -1 };

void Infix_To_Postfix::process_operator(char oper)
{
	if (operator_stack.empty() || ((oper == '(') || (oper == '[') || (oper == '{'))) {
		if (oper == ')' || oper == ']' || oper == '}') {
			throw Syntax_Error("Expression can't start with a closing parenthesis @ char: 0"); // TODO: Don't hardcode
		}
		operator_stack.push(oper);
	}
	else if (precedence(oper) > precedence(operator_stack.top())) {
		operator_stack.push(oper);
	}
	else {
		while (!operator_stack.empty()
			&& precedence(oper) <= precedence(operator_stack.top())
			&& operator_stack.top() != '('
			&& operator_stack.top() != '['
			&& operator_stack.top() != '{') {
			
			postfix += operator_stack.top();
			postfix += " ";
			operator_stack.pop();
		}

		if (oper == ')') {
			if (!operator_stack.empty() && operator_stack.top() == '(') {
				operator_stack.pop();
			}
			else {
				throw Syntax_Error("Unmatched closing parentheses @ char: 0"); // TODO: Don't hardcode
			}
		} 
		else if (oper == ']') {
			if (!operator_stack.empty() && operator_stack.top() == '[') {
				operator_stack.pop();
			}
			else {
				throw Syntax_Error("Unmatched closing parentheses @ char: 0"); // TODO: Don't hardcode
			}
		}
		else if (oper == '}') {
			if (!operator_stack.empty() && operator_stack.top() == '{') {
				operator_stack.pop();
			}
			else {
				throw Syntax_Error("Unmatched closing parentheses @ char: 0"); // TODO: Don't hardcode
			}
		}
		else {
			operator_stack.push(oper);
		}
	}
}

bool Infix_To_Postfix::is_operator(char the_char) const
{
	size_t position = OPERATORS.find(the_char);
	if (position != std::string::npos) {
		return true;
	}

	return false;
}

bool Infix_To_Postfix::is_special_operator(char the_char) const
{
	size_t position = SPECIAL_OPERATORS.find(the_char);
	if (position != std::string::npos) {
		return true;
	}

	return false;
}

int Infix_To_Postfix::precedence(char oper) const
{
	size_t position = OPERATORS.find(oper);
	return PRECEDENCE[position];
}

std::string Infix_To_Postfix::clean_tokens(std::string expression)
{
	std::istringstream infix_tokens(expression);
	std::string next_token, newly_tokenized;
	while (infix_tokens >> next_token) {
		for (int i = 0; i < next_token.size(); ++i) {
			if (isalnum(next_token[i])) {
				newly_tokenized += next_token[i];
				while (isalnum(next_token[i + 1])) {
					++i;
					newly_tokenized += next_token[i];
				}
				newly_tokenized += " ";
			}
			else if (is_operator(next_token[i])) {
				if (is_operator(next_token[i+1])) {
					char check = check_two_symbol_operator(next_token[i], next_token[i+1]);
					if (check == '?') {
						newly_tokenized += next_token[i];
					}
					else {
						newly_tokenized += check;
					}
				}
				else {
					newly_tokenized += next_token[i];
				}
				newly_tokenized += " ";
			}
		}
	}

	return newly_tokenized;
}

char Infix_To_Postfix::check_two_symbol_operator(char one, char two)
{
	if (one == '+' && two == '+') {
		return '~';
	}
	else if (one == '-' && two == '-') {
		return '_';
	}
	else if (one == '>' && two == '=') {
		return '@';
	}
	else if (one == '<' && two == '=') {
		return '#';
	}
	else if (one == '=' && two == '=') {
		return '=';
	}
	else if (one == '!' && two == '=') {
		return 'n';
	}
	else if (one == '&' && two == '&') {
		return '&';
	}
	else if (one == '|' && two == '|') {
		return '|';
	}
	else {
		return '?'; // Just two operators next to each other (e.g. parentheses)
	}
}

void Infix_To_Postfix::get_real_operator_symbols(char oper)
{
	if (oper == '!' || oper == '^' || oper == '*' || oper == '/' || oper == '%' ||
		oper == '+' || oper == '-' || oper == '>' || oper == '<') {
		postfix += oper;
	}
	else if (oper == '~') {
		postfix += '+';
		postfix += '+';
	}
	else if (oper == '_') {
		postfix += '-';
		postfix += '-';
	}
	else if (oper == 'n') {
		postfix += 'n';
	}
	else if (oper == '@') {
		postfix += '>';
		postfix += '=';
	}
	else if (oper == '#') {
		postfix += '<';
		postfix += '=';
	}
	else if (oper == '=') {
		postfix += '=';
		postfix += '=';
	}
	else if (oper == '$') {
		postfix += '!';
		postfix += '=';
	}
	else if (oper == '&') {
		postfix += '&';
		postfix += '&';
	}
	else if (oper == '|') {
		postfix += '|';
		postfix += '|';
	}
}

void Infix_To_Postfix::final_format()
{
	std::string old_postfix = postfix;
	postfix = "";
	std::istringstream infix_tokens(old_postfix);
	std::string next_token;
	
	while (infix_tokens >> next_token) {
		if (is_special_operator(next_token[0])) {
			get_real_operator_symbols(next_token[0]);
		}
		else {
			postfix += next_token;
		}
		postfix += " ";
	}
}

std::string Infix_To_Postfix::convert(const std::string & expression)
{
	postfix = "";
	while (!operator_stack.empty()) {
		operator_stack.pop();
	}

	std::string newly_tokenized = clean_tokens(expression);
	std::istringstream infix_tokens(newly_tokenized);
	std::string current_token, next_token;
	std::string previous_token = "";

	while (infix_tokens >> current_token) {
		if (is_operator(current_token[0])) {
			infix_tokens >> next_token;
			if (current_token[0] == '-') {
				if (isalnum(previous_token[0]) && isalnum(next_token[0])) {
					process_operator(current_token[0]);
					current_token = next_token;
				}
				else if (next_token[0] == '-') {
					process_operator('_');
				}
				else {
					process_operator('n');
					current_token = next_token;
				}
			}
			else if (is_operator(next_token[0])) {
				char temp = check_two_symbol_operator(current_token[0], next_token[0]);
				if (temp == '?') {
					if (current_token[0] == '-') {
						process_operator('n');
						process_operator(next_token[0]);
					}
					else if (next_token[0] == '-') {
						process_operator(current_token[0]);
						process_operator('n');
					}
					else {
						process_operator(current_token[0]);
						process_operator(next_token[0]);
					}
				}
				else {
					process_operator(temp);
				}
			}
			else {
				process_operator(current_token[0]);
				current_token = next_token;
			}
		}
		if (isalnum(current_token[0])) {
			for (int i = 0; i < current_token.length(); i++) {
				if (current_token[i] == ' ') {
					break;
				}
				postfix += current_token[i];
			}
			postfix += " ";
		}
		if (!is_operator(current_token[0]) && ! isalnum(current_token[0])) {
			throw Syntax_Error("Invalid character @ char: 0"); // TODO
		}
		previous_token = current_token;
	}

	while (!operator_stack.empty()) {
		char oper = operator_stack.top();
		operator_stack.pop();
		if (oper == '(' || oper == '[' || oper == '{') {
			throw Syntax_Error("Unmatched open parentheses @ char: 0"); // TODO
		}
		postfix += oper;
		postfix += " ";
	}
	final_format();
	return postfix;
}
