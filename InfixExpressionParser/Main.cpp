#include <stack>
#include <string>
#include "Evaluator.h"

/* 
Name: Ryan Kildea
Date: 06/28/18
CS 303

This program takes a mathematical expression, parses and primes it, then
sends it to an evaluator where it is analyzed and the result is output. */

int main() {
	Evaluator e;

	std::string expression = "5 * (-(7) * 3+8)";

	try {
		int result = e.evaluate(expression);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}