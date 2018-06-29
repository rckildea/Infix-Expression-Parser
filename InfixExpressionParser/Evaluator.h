#pragma once
#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include "Parser.h"

/* Evaluates the parser-formatted user expression */
class Evaluator {
public:
	/** Takes an expression formatted by the parser and evaluates the expression
	@param expression The parser-formatted expression
	@return The result of the expression
	*/
	int evaluate(std::string & expression);
private:
	std::stack<std::string> operator_stack;
	std::stack<int> operand_stack;
	std::string original_expression;

	/** Evaluates a sub-expression
	@param rhs The right hand side of the expression
	@param op The operator
	@return The result of the sub-expression
	*/
	void calculate(int rhs, char op);

	/** Determines the precedence of operators
	@param current The most recently read operator
	@param top The operator on top of the stack
	@return True (new operator is higher precedence) or false (old operator is higher precedence)
	*/
	bool higher_precedence(std::string current, std::string top);

	/** Determines whether or not the currently analyzed operator is a unary operator
	@param op The operator
	@return True or false
	*/
	bool is_unary(char op);

	/** Returns the matching open parenthesis for a closed parenthesis
	@param p The closing parenthesis
	@return The matching open parenthesis
	*/
	std::string get_matching_parenthesis(std::string p);

	/** Handles procedure when the equation tries to divide by zero
	*/
	void divided_by_zero();
};

