#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
bool infix_to_postfix(string infix, string& postfix);
bool bracket_check(string infix);
bool syntax_check(char check, string infix, int pos);
bool operands_in_map(string postfix, const Map& values);
bool evaluate_postfix(string postfix, const Map& values, int& result);

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	assert(evaluate("e / i", m, pf, answer) == 0 && pf == "ei/" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	cout << "Passed all tests" << endl;
}

int evaluate(string infix, const Map& values, string& postfix, int& result) {
	// Evaluates an integer arithmetic expression
	//   If infix is syntactically valid and all its lower case operand letters appear in the values map, then if evaluating the expression
	//     (using for each letter in the expression the value in the map that corresponds to it) attempts to divide by zero, then result
	//     is unchanged and the function returns 3; 
	//   otherwise, result is set to the value of the expression and the function returns 0.
	
	// infix is not syntactically valid -> return 1
		// postfix is modified by infix_to_postfix, but that's allowed
	if (!infix_to_postfix(infix, postfix))
		return 1;

	// infix is syntactically valid and converted to postfix, but not all operands appear in values map -> return 2
	if (!operands_in_map(postfix, values))
		return 2;

	// infix is syntactically valid, converted to postfix; all operands appear in values map, but expression involves dividing by zero -> return 3
	if (!evaluate_postfix(postfix, values, result))
		return 3;

	// everything good, result udpated appropriately by evaluate_postfix, return 0
	return 0;
}

bool infix_to_postfix(string infix, string& postfix) {
	//  checks whether infix is syntactically correct and converts infix to postfix

	// checking whether all brackets (if any) occur in valid pairs
	if (!bracket_check(infix))
		return false;

	postfix = ""; // initialising postfix to the empty string

	// removing spaces from string (to make rest of evaluation simpler)
	string no_spaces;
	for (int i = 0; i != infix.size(); i++)
		if (infix[i] != ' ')
			no_spaces += infix[i];
	infix = no_spaces; // updating infix

	// to keep track of operand and operator counts
	int operand_count = 0;
	int operator_count = 0;

	stack<char> op_stack; // stack of operators

	// iterating over infix
	for (int i = 0; i != infix.size(); i++) {

		// current char variable
		char c_char = infix[i];

		// if operand, append to postfix
		if (c_char >= 'a' && c_char <= 'z') {
			postfix += c_char;
			operand_count++; // incrementing operand count
			continue;
		}

		switch (c_char) {
			// push opening paranthesis onto operator stack
		case '(': 
			// if closing parenthesis, pop stack until we see opening parenthesis and add everything to postfix
			op_stack.push(c_char);
			break;
			
		case ')':
			while (op_stack.top() != '(') {
				postfix += op_stack.top();
				op_stack.pop();
			}
			op_stack.pop(); // remove the '('
			break;
			// c_char is an operator
		case '+':
		case '-':
		case '/':
		case '*':
			
			operator_count++; // incrementing operator_count
			// while stack isn't empty and top isn't '('
			while (op_stack.size() != 0 && op_stack.top() != '(') {
				// if c_char doesn't have higher precedence than top, update postfix and pop op_stack
				if (c_char == '+' || c_char == '-' || op_stack.top() == '*' || op_stack.top() == '/') {
					postfix += op_stack.top();
					op_stack.pop();
				}
				// c_char has higher precedence than top
				else break;
			}
			// push c_char onto stack
			op_stack.push(c_char);
			break;
		// syntax check:
			// if we fall through to default, it means the char is not a lower-case letter, a valid operator or a bracket
			// char is therefore syntactically invalid
		default:
			return false;
		}

		// checking syntax
			// when we reach here, c_char is either an opening bracket, a closing bracket, an operand or an operator
		if (!syntax_check(c_char, infix, i))
			return false;
	}

	// while stack isn't empty, append to postfix and pop op_stack
	while (op_stack.size() != 0) {
		postfix += op_stack.top();
		op_stack.pop();
	}

	// syntax check: number of operators must be 1 less than number of operands
	if (operator_count != operand_count - 1)
		return false;

	return 1;
}


bool syntax_check(char check, string infix, int pos) {
	// returns false if syntax is incorrect, true otherwise
	
	/* Rules for a syntactically valid postfix expression (space characters are ignored)
	The expression must only have valid operators, brackets, and lower-case letters
	An operator must be followed by an operand or an opening bracket
	An operand must either be at the end of the expression or must be followed by an operator or a closing bracket
	Number of operators must be one less than the number of operands */

	// if next_char remains a space character, the current character is at the end of the expression
	// else, next_char is the character immediately after the "check" character
	char next_char = ' ';
	if (pos + 1 != infix.size())
		next_char = infix[pos + 1];

	// an operand must either be at the end of the expression or must be followed by an operator or a closing bracket
	if (check >= 'a' && check <= 'z') {
		switch (next_char) {
		case ' ': // reached end of expression
		// next character is an operator
		case '*':
		case '/':
		case '+':
		case '-':
		case ')':
			return true;
		// next character is an operand or an opening bracket
		default:
			return false;
		}
	}

	// opening bracket must be followed by either an operand or another opening bracket
	if (check == '(') {
		if (next_char == ' ' || next_char < 'a' || next_char > 'z')
			if (next_char != '(')
				return false;
	}
	// operator must be followed by an operand or an opening bracket
	else if (check == '*' || check == '/' || check == '+' || check == '-') {
		if (next_char == ' ')
			return false;
		switch (next_char) {
			case '+': 
			case '-': 
			case '/': 
			case '*':
				return false;
		}
	}

	// infix is syntactically valid
	return true;
}

bool bracket_check(string infix) {
	// Every opening bracket must have a corresponding closing bracket
	// checks whether all opening and closing brackets in infix occur in valid pairs
	string brackets_only;

	for (int i = 0; i != infix.size(); i++)
		if (infix[i] == '(' || infix[i] == ')')
			brackets_only += infix[i];
	
	if (brackets_only.size() == 0)
		return true;

	// comparing number of brackets
	int open_brackets = 0;
	int closed_brackets = 0;

	for (int i = 0; i != brackets_only.size(); i++)
		switch (brackets_only[i]) {
			case '(': open_brackets++; break;
			case ')': closed_brackets++; break;	
	}

	// there should be equal number of open and closed brackets
	if (open_brackets != closed_brackets)
		return false;

	// if not yet returned, we have a nonzero and equal number of open brackets and closed brackets
	int current_open = 0;
	for (int i = 0; i != brackets_only.size(); i++) {
		// open bracket
		if (brackets_only[i] == '(')
			current_open++;
		// closed bracket
		else {
			current_open--;
			// if at any point in the string there are more closed brackets than open brackets, the string is syntactically invalid
			if (current_open < 0)
				return false;
		}
	}

	// if not yet returned, we have a string with equal number of opening and closing brackets, 
		// and up to no index i of the string are there more closing brackets than opening brackets -> string is syntactically valid
	return true;
}

bool operands_in_map(string postfix, const Map& values) {
	// infix is syntactically valid, postfix has been modified to the correct postfix expression
		// checking whether all operands appear in the values map by iterating over postfix
	for (int i = 0; i != postfix.size(); i++) {
		char c_char = postfix[i];
		if (c_char >= 'a' && c_char <= 'z')
			// return false if c_char not in values map
			if (!values.contains(c_char))
				return false;
	}
	// all operands present in map
	return true;
}

bool evaluate_postfix(string postfix, const Map& values, int& result) {
	// if the postfix expression can be properly evaluated, evaluate_postfix evaluates it, updates result and returns true
	// if evaluating the postfix expression involves dividing by zero, evaluate_postfix leaves result unchanged and returns false

	/* Pseudocode
		Initialize the operand stack to empty
		For each character ch in the postfix string
			if ch is an operand
				push the value that ch represents onto the operand stack
			else // ch is a binary operator
				set operand2 to the top of the operand stack
			pop the stack
				set operand1 to the top of the operand stack
			pop the stack
			apply the operation that ch represents to operand1 and
					operand2, and push the result onto the stack
		When the loop is finished, the operand stack will contain one item,
		  the result of evaluating the expression*/

	// empty stack of operands
	stack<int> operand_stack;
	
	// iterating over postfix
	for (int i = 0; i != postfix.size(); i++) {
		char ch = postfix[i]; // current character we're examining

		// ch is an operand -> retrieve value from map and append to operand stack
		if (ch >= 'a' && ch <= 'z') {
			int val; 
			values.get(ch, val);
			operand_stack.push(val);
		}

		// ch is a binary operator
		else {
			// finding operands 2 and 1
			int operand2 = operand_stack.top();
			operand_stack.pop();
			int operand1 = operand_stack.top();
			operand_stack.pop();

			int eval;
			// evaluating operand1 and operand2 with operator ch
			switch (ch) {
			case '+': eval = operand1 + operand2;
				break;
			case '-': eval = operand1 - operand2;
				break;
			case '*': eval = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0) // evaluation attempts to divide by zero
					return false; // evaluation not possible
				eval = operand1 / operand2;
				break;
			}
			
			// pushing the result onto stack
			operand_stack.push(eval);
		}
	}

	// evaluation completed successfully; update result and return true
	result = operand_stack.top();
	return true;
}