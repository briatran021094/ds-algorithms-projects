/** Title: Evaluator cpp file
 * Class: CSC2431 Data Structures II
 * Purpose: Implements the Evaluate function to compute
 * the result of a postfix arithmetic expression using stack
 * Author: Bria Tran
 * Date: May 13th, 2025
*/

#include "evaluator.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stack>

using namespace std;

// Parameter: string& of a char from the stack
// Return: true if an operator
// Finds if the symbol from the stack is an operator
bool Operator(const string& op) {
	return op == "+" || op == "-" || op == "*" || op == "/" || op == "^";
}

// Parameter: string& of the a char from the stack
// Return: true if the symbol from the stack is a number
// Finds if the symbol from the stack is a number
bool Number(const string& str) {
	istringstream string(str);
	double val;
	return (string >> val) && string.eof();
}

// Parameter: string& of postfix, bool& of error
// Return: a double of the evaluated operation
// Evaluates the Postfix equation
double Evaluate(const string& postfix, bool& error) {
	istringstream iss(postfix);
	stack<double> problem;
	error = false;
	string sym;

	while (iss >> sym) {
		if (Number(sym)) {                             // If sym is a number -> push onto stack
			problem.push(stod(sym));
		} else if (Operator(sym)) {                    // If sym is an operator
			if (problem.size() < 2) {
				error = true;
				return 0;
			}
			double b = problem.top(); problem.pop();   // Pops the top 2 values from the stack and assigns to a and b
			double a = problem.top(); problem.pop();
			double result;

			if (sym == "+") result = a + b;            // Evaluate with the operands a and b
			else if (sym == "-") result = a - b;
			else if (sym == "*") result = a * b;
			else if (sym == "/") {
				if (b == 0) {
					error = true;
					return 0;
				}
				result = a / b;
			} else if (sym == "^") {
				result = pow(a, b);
			}
			problem.push(result);
		} else {                                       // If there is an invalid sym
			error = true;
			return 0;
		}
	}

	if (problem.size() != 1) {                 // Valid postfix should only have one value in the stack
		error = true;
		return 0;
	}
	return problem.top();
}