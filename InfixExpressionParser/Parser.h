#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


/* Takes a user expression and formats it to be easily analyzed by the evaluator */
class Parser {
public:
	/** Converts user expression into an expression easily interpretable by the evaluator
	@param expression The user expression
	@return The formatted expression
	*/
	static std::string Parse(std::string expression);
private:
	/** Verifies a character is an operator
	@param ch The character meant to represent an operator
	@return True or false
	*/
	static bool isoperator(char ch);

	/** Determines whether or not the currently analyzed operator is a binary operator
	@param char The operator
	@return True or false
	*/
	static bool is_binary_operator(char op);

	/** Verifies a character is a parenthesis
	@param ch The character meant to represent a parenthesis
	@return True or false
	*/
	static bool isparenthesis(char ch);

	/** Attempts to convert two detected one-char operators into a one-char operator representing their union
	@param char first The first char read in
	@param char second The second char read in
	@return The representative char (if match found), '?' (if no match found)
	*/
	static char process_double_operators(char first, char second);

	/** Negative, minus, and decrement all use '-'.  This function interprets the equation
	@param string token The most recently read token
	@param int i The current index of the token
	@param bool previous_was_digit True if the previous character was a digit
	@param bool previous_was_binary_operator True if the previous character was a binary operator
	@return The interpreted form of '-' or '--'
	*/
	static std::string handle_minus(std::string token, int i, bool previous_was_digit, bool previous_was_binary_operator);

	/** Checks for errors in the formatted expression
	@param string expression The formatted expression
	*/
	static void check_final_expression(std::string expression);
};

