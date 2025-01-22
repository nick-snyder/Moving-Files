/**
 * CS515 Assignment 2
 * File: evaluation.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 22 February 2022
 * Collaboration Declaration: online resources
 * Issue: doesn't like negative numbers
 */

// infix expression evaluation
// implemented with STL vector
// evalues expression with multiple digit numbers, * / + - and {} [] () paratheis
// assume the expression is well formatted with balanced braces.

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

// Generates a stack of string tokens representing postfix
// notation for the input line
void generateRPN(string line, stack<string> &postfix);

bool is_number(string str) {
	stringstream ss;
	ss << str;
	int temp;
	ss >> temp;
	if (ss.fail()) {
		return false;
	}
	else {
		return true;
	}
	// //for (int i = 0; i < str.length(); i++) {
	// 	if (isdigit(str[0]) == false )
	// 		return false; //when one non numeric value is found, return false
	// //}
	// return true;
}

int execute(stack<int> s, char oper) {

	// stack<int> tempstack = s;
	// int count = 0;
	// while (tempstack.top()) {
	// 	cout << tempstack.top() << endl;
	// 	tempstack.pop();
	// }
	// int leftOperand;
	// if (s.size() < 3) {
	// 	//cout << s.top() << endl;
	// 	//return s.top();
	// 	leftOperand = 0
	// } else {
	// 	leftOperand = s.top();
	// }

	int rightOperand = s.top();
	//cout << "Ro" << rightOperand << endl;
	s.pop();

	int leftOperand = s.top();

	//int leftOperand = s.top();
	//cout << "Lo" << leftOperand << endl;
	s.pop();

	//cout << leftOperand << oper << rightOperand << endl;

	int answer = 0;
	switch (oper) {
		case '+':
			answer = leftOperand + rightOperand;
			break;
		case '-':
			answer = leftOperand - rightOperand;
			break;
		case '*':
			answer = leftOperand * rightOperand;
			break;
		case '/':
			answer = leftOperand / rightOperand;
			break;
	}

	s.push(answer);
	//cout << "here"  << answer << endl;
	//cout << "Execute() is returning: " << answer << endl;
	return answer;
}

string evaluateRPN(stack<string> &postfix) {
	stack<int> copystack;
	//string next = "";
	string target = "";

	// reads stack into string
	stack<string> cstack;
	while (postfix.size() > 0) {
		cstack.push(postfix.top());	// string '12'
		postfix.pop();
	}

	// evaluates the string
	string operators = "+-*/";
	while (cstack.size() > 0) {
		target = cstack.top();
		cstack.pop();
		//out << "gg" << endl;
		//cout << copystack.top() << endl;

		// if target is a number
		if (is_number(target))
			copystack.push(stoi(target));

		// if target an operator
		else if (operators.find(target[0]) != std::string::npos) {
			//execute(copystack, target[0]);
			//printStack(copystack);
			//cout << copystack.top() << endl;

			//if (copystack.size() > 2) {
				cstack.push(to_string(execute(copystack, target[0])));
				//cout << "here" << endl;
				copystack.pop();
				//cout << "there" << endl;
				copystack.pop();
				//cout << "where" << endl;
			//}
			// cstack.push(to_string(execute(copystack, target[0])));
			// copystack.pop();
			// copystack.pop();
		}
	}

	return to_string(copystack.top());
}

int main(int argc, char ** argv) {
    string line;
    cout << "Expression: ";
    while (getline(cin, line)) {
        // skip empty line
        if (line.length() == 0)
            continue;

        stack<string> postfix;
        if (line == "exit")
            break;

        generateRPN(line, postfix);

        cout << "Answer: " << evaluateRPN(postfix) << endl;
        line.clear();
        cout << "Expression: ";
    }
    return 0;
}
