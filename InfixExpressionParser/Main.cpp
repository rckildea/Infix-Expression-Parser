#include <iostream>
#include <string>
#include "Node.h"
#include "Node.cpp"
#include "Stack.h"
#include "Infix_To_Postfix.h"
#include "Postfix_Evaluator.h"

using std::cout;
using std::endl;

int main() {
	/*Stack<std::string> a_stack;
	Stack<std::string> b_stack;

	a_stack.push("abc");
	a_stack.push("def");
	b_stack.push("ghi");

	cout << a_stack.top() << "     " << b_stack.top() << endl;*/

	std::string equation = "++7+8*5";
	Infix_To_Postfix converter;

	cout << "\n" << equation << endl;

	equation = converter.convert(equation);

	cout << "\n" << equation;

	Postfix_Evaluator evaluator;

	int x = evaluator.eval(equation);

	return 0;
}