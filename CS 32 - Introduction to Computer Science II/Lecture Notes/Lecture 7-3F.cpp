#include <string>
#include <iostream>
using namespace std;


// IMPLEMENTING NODE FOR A DOUBLY LINKED LIST
struct Node {
		// each node now has a pointer to the successor node and the predecessor node
	int value;
	Node* next; 
	Node* prev;
};

int main() {
	// the advantage of linked lists lies in cheap insertions and deletions; the disadvantage lies in expensive random access 
		// (if the data you're trying to access are in the middle of the list), 
		// since you need to go through all the elements before or after the element you're looking for to find it

	// when implementing linked lists, ALWAYS CHECK THE SPECIAL CASES
		// normal (in middle), empty, front, back, one-element, (maybe) two elements

	// circular list
		// when the m_next pointer of the last Node points to the first Node in the list, 
			// it makes things easier for us since we now don't need to check whether m_next is a null pointer each time we access a Node
		// we can still check whether we've hit the end of the list by comparing m_next to m_head

	// in a doubly-linked circular list, we don't need to maintain an m_tail anymore since m_head->m_prev is basically a pointer to the last element
		// however, we do still need to worry about the special case where there aren't any nodes whatsoever (m_head would then be a nullptr)
		// one way to resolve this issue is by using a dummy node
	
	/* DUMMY NODE IMPLEMENTATION
		// every circular list, no matter how big, has a node preceding it and a node following it
			// the head points to the dummy node, the dummy node points to the first node, and the last node points to the dummy node
		// this means there are no special cases at all
	*/
}

void transfer(Account* from, account& to, double amt) {
		// what happens if /from/ and /to/ are the same account?
		// this is called "aliasing," a situation where multiple names refer to the same object
		// the candidates for where aliasing might occur are typically where you have a function with multiple pointers or references to the same type of object
	if (&from != &to) { // to protect against aliasing, since we're comparing the addresses of the variables
			
		if (from.balance() >= amt) {
			from.debit(amt);
			from.credit(amt);
			// if the debit and credit functions merely subtract and add money here, aliasing would be harmless
			// however, say, there's a fee associated with crediting and debiting -> aliasing would be harmful, since the account would be charged
		}
		else
			cout << "Insufficient balance" << endl;
	}
	else
		cout << "Cannot transfer" << endl;
}

String& String::operator=(const String& rhs) {
	if (this != &rhs) {
		// this approach to deal with aliasing (while still widely used) has one flaw:
				/* what if the "new" used to allocate a new array for the string fails?
					here, an exception is thrown, the exception propagates through functions, destructors are called multiple times, and the program crashes
				*/
		String temp(rhs); // we try to create a new String
			// say the copy constructor tries to allocate the necessary memory to create temp, and fails
			// the constructor will exit when it fails, but temp will remain in use, and we won't have a crashing program as the exception elevates
		swap(temp); // we gave string a member function swap
			// if the copy constructor does not fail, we can just call swap on the String object and the constructed copy to have the desired result
	}
}