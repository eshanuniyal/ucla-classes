#include <string>
#include <iostream>
using namespace std;



void func() {

	// THREE USES OF ARRAYS:

	// fixed-size array -> size known at compile time
	int a[100];

	// dynamically-allocated array -> size does not need to be known at compile time
	int length = 144
	int* ip = new int[length];
	...;
	delete[] ip;

	// resizable array -> if we run out of space in the array, we can create a new larger array, copy all elements from the first, and delete the old one
	int* ip = new int[length];
	if (...full...) {
		int new_length = ...; // some factor of old capacity, say, 2 * length
		int* ip2 = new int[new_length]; // create new, larger array
		for (int i = 0; i != length; i++) // copy elements from first array to second array
			ip2[i] = ip[i];
		delete[] ip; // delete first array
		ip = ip2; // update the pointer in ip
		length = new_length; // update the capacity (so we can appropriately check whether we're accessing out-of-bounds later)

	// however, with any of these array types, removing elements (and keeping the order) is quite expensive, since the entire array needs to be moved left
	}
}

// IMPLEMENTING NODE FOR A SINGLY LINKED LIST
struct Node {
	// the information we need to keep is the datum of interest (e.g. int, string) and a pointer to the next datum of interest
	int value;
	Node* next; // note: Node next; wouldn't work, since that creates an infinite recursive list of Node objects inside Node objects
		// we indicate the end of the list by using the nullptr in the last Node
	Node* prev; // adding this makes the Node struct part of a DOUBLY-LINKED LIST
};

int main() {
	Node first; // creates a Node -> we don't use this, because we can't create an empty list like this
	Node* head = nullptr; // better practice -> we can now have a 0 length list, by initialising head itself to a nullptr

	while (head != nullptr) { // WRONG -> if we change head, we've lost the list -> memory lost
		cout << head->value << endl;
		head = head->next;
	}

	Node* current_ptr = head;
	while (current_ptr != nullptr) { // appropriate implementation
		cout << current_ptr->value << endl;
		current_ptr = current_ptr->next;
	}

	// better implementation:
	for (Node* p = head; p != nullptr; p = p->next)
		cout << p->value << endl;

	// whenever we follow p, we must check for two things:
		// p must have previously been given a value
		// p must not be a nullptr
	// in the for loop we wrote above, p can never be a nullptr when the cout statement is written
	// p gets a value in one of two ways:
		// from head
		// from p->next (next element in linked list)
	// we therefore need to be sure that head is well-defined /and/ p->next is a defined pointer ---> list must be properly constructed

	// --------------------------------------------------------------------------------------------
	// how do we find a node with a particular value (say, 42) (we don't know whether it exists)
	Node* p;
	for (p = head; p != nullptr && p->value != 42; p = p->next) { ; }
		// this loop does all the work for us: it only breaks when p is either a nullpointer or points to the right Node object
		// we check whether p != nullptr first to make sure we aren't following a nullptr in the second condition
		// only after that do we check whether p->value != 42

	if (p != nullptr)
		cout << p->value << endl; 
	else
		cout << "42 is not in the list." << endl;

	// --------------------------------------------------------------------------------------------
	// insert a new value (say, 36) after a given value (say, 42)
	Node* p;
	for (p = head; p != nullptr && p->value != 42; p = p->next) { ; }
	if (p != nullptr) {
		// creating a new node
		Node* new_element = new Node; // pointer to new Node
		new_element->value = 36; // update the value of the new Node to 36, and the next pointer so it points to 87
		new_element->next = p->next; // making new Node point to the element currently after 42 (say, 87)
		p->next = new_element; // have 42 point to new Node; effectively inserts it into the list (we already linked 87 to new Node)
		
	}
	// DON'T DO THESE THINGS IN THE WRONG ORDER
		// set values in a new node first

	// --------------------------------------------------------------------------------------------
	// finding the first occurrence of an element (if any; say, 42) and deleting it
		// here, it's helpful to have a doubly-linked list, since that would allow us to not have to keep track of two pointers (one to 42, one to the element before 42) all the time
		// with a doubly-linked list, we can just find the one Node and know which elements come before and after it (so we can link them)
	Node* p;
	for (p = head; p != nullptr && p->value != 42; p = p->next) { ; } // finding 42
	if (p != nullptr) { // if 42 was found
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}

	// --------------------------------------------------------------------------------------------
	// adding an element in a doubly-linked list (say, 36) after a certain element (say, 42)
	Node* p;
	for (p = head; p != nullptr && p->value != 42; p = p->next) { ; } // finding 42
	
	if (p != nullptr) { // if 42 was found

		Node* new_element = new Node;
		new_element->value = 36;
		new_element->next = p->next;
		new_element->prev = p;
		
		p->next = new_element;
		new_element->next->prev = new_element;
	}

	// --------------------------------------------------------------------------------------------
	// accessing elements from the tail of a list
		// here, we create a tail pointer to enable that optimisation
	Node* tail;

	// the advantage of linked lists lies in cheap insertions and deletions; the disadvantage lies in expensive random access 
		// (if the data you're trying to access are in the middle of the list), 
		// since you need to go through all the elements before or after the element you're looking for to find it
}

