#include <iostream>
#include <string>
using namespace std;

struct Node{
	string data;
	vector<Node*> children;
	Node* parent;
};


int count(const Node* p) {
	// count the number of nodes in a tree given pointer to root node
	// we could use a stack to move through the tree and find the number or nodes, or we could just use the (more elegant) recursive solution
	
	// base case: tree is empty
	if (p == nullptr)
		return 0;

	int total = 1; // running total is 0, since we're counting ourselves

	// finding number of children
	for (int i = 0; i != p->children.size(); i++)
		total += count(p->children[i]);

	return total;
}

void printTree(const Node* p, int indent = 0) {
	// print the tree in an indented manner
	
	// not a base case, but rather a special case of nullptr passed in -> do nothing
	if (p == nullptr)
		return;

	// string(2 * indent, ' ') gives us the proper indentation
	cout << string(2 * indent, ' ') << p->data << endl;

	for (int i = 0; i != p->children.size(); i++)
		// cout << "  "; 		// this doesn't work; the first element in the children array will be indented, but everything below it will have the same indentation
		printTree(p->children[i], indent + 1);
				// we use indent + 1, not indent++, since we don't want more indentation for /each/ child
}


// printTree is an example of a function that's going to do a "preorder traversal" of the tree; each node is processed before its children
// the opposite kind of algorithm is a "postorder traversal"; each node is processed after its children
// it's not always clearcut whether an algorithm involves preorder traversal or postorder traversal - the count function could be argued to be either

/* Definition: A binary tree is either:
		empty, or
		a node with a left binary subtree and a right binary subtree
*/

struct Node{
	// node in a binary tree
	string data;
	Node* left;		// pointer to root node of left subtree
	Node* right;	// pointer to root node of right subtree
};

struct Node{
	// node in a binary tree representing a family hierarchy
	string data;
	Node* oldestChild;
	Node* nextYoungerSibling;
};


/* a binary tree representing the royal family (starting from Charles)
left node is given by /
right node is given by --------
					Charles
				    /
				William ------- Harry
				/				/
			   /			Archie
			  /
			George ------- Charlotte -------- Louis

*/

/* a Binary Search Tree is either
		empty, or
		a node with a left BST and a right BST such that
			the value at every node in the left BST is < the value at this node, and
			the value at every node in the right BST is > the value at this node
*/

// STL gives us data structures based on binary search trees

#include <map>
using namespace std

int main(){

	map<string, double> ious;

	string name;
	double amt;

	while (cin >> name >> amt)
		ious[name] += amt;

	cout << ious.size() << endl;

	if (ious.find("Ricky") == ious.end())
		cout << "Ricky is not in the map" << endl;

	// prints the key, value pairs in order
	for (map<string, double>::iterator p = ious.begin(); p != ious.end(); p++)
		cout << p->first << " owes me " << p->second << endl;
}

#include <set>
using namespace std;

int main(){

	set<string> visitors;

	...
	string name;
	visitors.insert(name);

	cout << visitors.size() << endl;

	if (visitors.find("Ricky") == visitors.end())
		cout << "Ricky not found" << endl;

	for (map<string, double>::iterator p = ious.begin(); p != ious.end(); p++)
		cout << *-p << endl;	// prints the visitors in no particular order
}