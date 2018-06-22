#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "Stack.h"
#include "Infix_To_Postfix.h"
#include "Postfix_Evaluator.h"

using std::cout;
using std::endl;

int main() {
	Infix_To_Postfix converter;
	Postfix_Evaluator evaluator;
	std::vector<std::string> equations;
	std::vector<int> answers;

	std::string abc = "(8*-42 / (3 +4-4+1-2))^2";
	abc = converter.convert(abc);
	cout << abc << endl;
	int x = evaluator.eval(abc);
	cout << x << endl;

	/*equations.push_back("(8*-42 / (3 +4-4+1-2))^2");*/

	//for (std::vector<std::string>::iterator iter = equations.begin(); iter != equations.end(); ++iter) {
	//	answers.push_back(evaluator.eval(converter.convert(*iter)));
	//}

	//for (std::vector<int>::iterator iter2 = answers.begin(); iter2 != answers.end(); ++iter2) {
	//	cout << *iter2 << endl;
	//}



	return 0;
}

void test_project() {
	Infix_To_Postfix converter;
	Postfix_Evaluator evaluator;
	std::vector<std::string> equations;
	std::vector<int> answers;

	equations.push_back("! 1"); // logical not
	equations.push_back("! 0");

	equations.push_back("++7"); // prefix increment
	equations.push_back("--6"); // prefix decrement

	equations.push_back("-3"); // negative

	equations.push_back("5^3"); // power

	equations.push_back("6 * 2"); // multiplication
	equations.push_back("6 / 2"); // division
	equations.push_back("6 % 2"); // modulo

	equations.push_back("7 + 8"); // addition
	equations.push_back("7 - 8"); // subtraction

	equations.push_back("8 > 7"); // greater than
	equations.push_back("8 >= 7"); // greater than/equal to
	equations.push_back("8 < 7"); // lesser than
	equations.push_back("8 <= 7"); // lesser than/equal to

	equations.push_back("9 == 9"); // equality
	equations.push_back("9 != 9"); // inequality

	equations.push_back("6 > 5 && 4 > 5"); // logical and

	equations.push_back("1 || 0"); // logical or

								   /*
								   0
								   1
								   8
								   5
								   -3
								   125
								   12
								   3
								   0
								   15
								   -1
								   1
								   1
								   0
								   0
								   1
								   0
								   0
								   1
								   */

	for (std::vector<std::string>::iterator iter = equations.begin(); iter != equations.end(); ++iter) {
		answers.push_back(evaluator.eval(converter.convert(*iter)));
	}

	for (std::vector<int>::iterator iter2 = answers.begin(); iter2 != answers.end(); ++iter2) {
		cout << *iter2 << endl;
	}
}