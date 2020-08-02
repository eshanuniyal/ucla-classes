#include <string>
#include <iostream>
using namespace std;


// a pattern of behaviour where we only add or remove elements from the end is called a STACK
	// the item most recently added is at the top of the stack, and only elements at the top of the stack may be removed


struct Stack {
	// basic functionality of any library implementation of a stack:
		// Create a stack
		// push an item onto the stack			i.e. insert an item at the end of the stack (if the stack is implemented with fixed capacity, it shouldn't be full)
		// pop an item from the stack			i.e. remove an item at the top of the stack (if stack isn't empty)
		// look at the top item of the stack	(if stack isn't empty)
		// is the stack empty?
	// additional functions that implementations may or may not have:
		// how many items are in the stack?
		// look at any item in the stack		if stack is implemented in such a way that we can look at any element in the stack
};

#include <stack> // defines std::stack from C++ library
using namespace std;

int main() {
	stack<int> s; // an empty stack s that holds integers
	s.push(10);
	s.push(20);
	int n = s.top(); // top() returns to us the top item in the stack; in this case, 20
	s.pop(); // pop() removes the last item in the stack; now, stack has only one value, 10
		// pop() doesn't return a value
	if (!s.empty()) // empty() returns true if stack is empty
		cout << "s has " << s.size() << " elements" << endl;
			// standard library implementation of stack allows us to ask about the size of the stack
	// however, standard library implementation does not allow us to look at any member of the stack but its top

	// if the stack is empty, calling pop() or top() on the stack is undefined behaviour

	// the main reason we would use stacks rather than arrays (which have more functionality) would be for human readability
		// the limited nature of the stack is a good thing, since it makes clear what we're doing
}

// QUEUE
	// a queue is kind of like a stack, except only insertions happen on one end and only deletions happen on the other
	// the end where insertions happen is a tail (or back), and the end where deletions happen is the head (or front)

struct Queue {
	// basic functionality of a library implementation of a queue:
		// Create a queue
		// enqueue an item						i.e. insert an item at the tail of the queue 
		// dequeue an item						i.e. remove an item at the head of the queue (if queue isn't empty)
		// look at the head of the queue		(if queue isn't empty)
		// is the queue empty?
	// additional functions that implementations may or may not have:
		// how many items are in the queue?
		// look at any queue in the stack		if queue is implemented in such a way that we can look at any element in the queue
};

#include <queue> // defines std::queue
using namespace std;

int main() {
	queue<int> s; // an empty queue s that holds integers
	s.push(10);	// notation for enqueueing items is similar to that of stacks, even though we say items are enqueued rather than pushed
	s.push(20);
	int f = s.front(); // front() returns to us the front item in the queue; in this case, 10
		// we are looking at the item that was first added i.e. item least recently added
	int b = s.back(); // back() returns to the back or tail or item of the queue; rarely used
		// we are looking at the item last added i.e. item most recently added
	s.pop(); // notation for dequeueing items is similar to tha tof stacks, even though we say items are dequeued rather than popped
		// pop() removes the last item in the stack; now, stack has only one value, 10
		// pop() doesn't return a value
	if (!s.empty()) // empty() returns true if queue is empty
		cout << "s has " << s.size() << " elements" << endl;
	// standard library implementation of queue allows us to ask about the size of the stack
	// however, standard library implementation does not allow us to look at any member of the queue
	// if the queue is empty, calling pop() or top() on the queue is undefined behaviour
}

// NOTE
	// you may sometimes see a stack as being referred to as a LIFO data structure (Last  In First Out)
	// you may sometimes see a queue as being referred to as a FIFO data structure (First In First Out)

// -------------------------------------------------------------------------------------------------------------
// prefix notation:
f(a, b, c);
add(sub(8, div(6, 2)), 1) // is equivalent to 
+ - 8 / 6 2 1 // is equivalent to
(8 - (6 / 2)) + 1 // infix notation
	// with infix notation, we need additional rules to not have to deal with brackets
		// multiplication and division have higher precedence than addition and subtraction
		// operations with equal precedence are evaluated left to right
// postfix notation:
8 6 2 / - 1 +
	// this allows us to evaluate the expression with only two left-to-right passes
8 6 2 / - 1 +		-> 8 3 - 1 +		-> 8 3 - 1 +		-> 5 1 + -> 6

// converting infix to postfix
	// if it's an operand, append to the result sequence
	// if it's an operator:
		// if stack is empty, push the operator onto the operator stack
		// else if the precedence of the current operator > the precedence of the top of the stack, push current operator
		// else pop the top item from the stack and append it to the result sequence, then check again
// e.g. 
8 - 6 / 2 + 1 // infix expression
// operator stack		// result sequence
						8
-						8
-						8 6
- /						8 6
- /						8 6 2
-						8 6 2 /			// + has less precedence than /, so / is popped and added to result sequence
						8 6 2 / -		// + does not have strictly greater precedence than -, so - is popped and added to result sequence
+						8 6 2 / -
+						8 6 2 / - 1
						8 6 2 / - 1 +	// this is the postfix version of our initial infix expression
// rules with parantheses:
	// if it's an operand, append to the result sequence
	// if it's an open parenthesis, push it onto the stack
	// if it's a close parenthesis:
		// while the top of the stack is not an open parenthesis
		// pop the top item of the stack and append it to the result sequence, then check again
	// if it's an operator:
		// if stack is empty or the top is an open parenthesis, push the operator
		// else if the precedence of the current operator > the precedence of the top of the stack, push current operator
		// else pop the top item from the stack and append it to the result sequence, then check again
// e.g.
8 * ((2 + 2) - (9 - 6)) - 2
// operator stack		// result sequence
						8
*						8
* (						8
* ( (					8
* ( (					8 2
* ( ( +					8 2
* (						8 2 2 +
* ( -					8 2 2 +
* ( - (					8 2 2 +
* ( - (					8 2 2 + 9
* ( - ( -				8 2 2 + 9 6
* ( -					8 2 2 + 9 6 -
*						8 2 2 + 9 6 - -
						8 2 2 + 9 6 - - *
-						8 2 2 + 9 6 - - *
-						8 2 2 + 9 6 - - * 2
						8 2 2 + 9 6 - - * 2 - // postfix expression
