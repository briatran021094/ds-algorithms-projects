/** Title: Evaluator header file
* Class: CSC2431 Data Structures II
 * Purpose: Header file for evaluator
 * Author: Bria Tran
 * Date: May 13th, 2025
*/

#ifndef EVALUATOR_H
#define EVALUATOR_H


#include <string>
using std::string;

double Evaluate(const string& postfix, bool& error);
bool Operator(const string& op);
bool Number(const string& str);

#endif