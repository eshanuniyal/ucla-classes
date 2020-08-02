// #########################################################################################################
// C++ STANDARD TEMPLATE LIBRARY (STL)
/* The library provides various types and functions:
	- Stacks and queues
	- Vectors (dynamically resizeable array)
*/

#include <vector>
using namespace std;

int main() {
	vector<int> vi; // initialised with size 0
	vi.push_back(10);
	vi.push_back(20);
	vi.push_back(30);
	cout << vi.size(); // writes 3
	cout << vi.front(); // writes 10
	cout << vi.back(); // writes 30
	vi[1] = 40;
	// vi[3] = 50; would be undefined behavior
	for (size_t k = 0; k < vi.size(); k++)
		cout << vi[k] << endl;
	// writes 10 40 30, one per line
	vi.pop_back(); // removes item at back
	for (size_t k = 0; k < vi.size(); k++)
		cout << vi[k] << endl;
	// writes 10 40, one per line
	vi.at(1) = 60; // equivalent to v[1] = 60;
		// difference is, if the index is out of bounds, we'll get an exception instead of being undefined behaviour
	vi.at(3) = 70; // throws exception
	vector<double> vd(10);
	// vd.size() is 10, each element is 0.0
	vector<string> vs(10, "Hello");
	// vs.size() is 10, each element is "Hello"
	int a[5] = { 10, 20, 30, 40, 50 };
	vector<int> vx(a, a + 5);
	// vx.size() is 5, vx[0] is 10, vx[1] is
	// 20, ..., vx[4] is 50

	// -------------
	vector<int> vi;
	vi[0] = 10; // undefined behaviour; vi.size() is 0, so you can't use index 0
}

// #########################################################################################################
#include <list>
#include <string>

using namespace std;
int main() {
	list<int> li;
	li.push_back(20);
	li.push_back(30);
	li.push_front(10);
	//	li.begin()		li.end()
	//	v				v
	//	10		20		30
	cout << li.size(); // writes 3
	cout << li.front(); // writes 10
	cout << li.back(); // writes 30
	li.push_front(40);
	li.pop_front(); // not available with vectors, since it's expensive for a vector but cheap for a linked list
		// square bracket operator is not provided for indexing a list, since finding elements by index is expensive for a linked list

	
	for (list<int>::iterator p = li.begin();
		p != li.end(); p++)
			// p is not literally a pointer; p++ would give us the next memory location, not the next element
			// an iterator is a generalisation of the idea of a pointer; we create iterator p here by using the type 
				// list<int>::iterator
			// p++ /effectively/ gives us a pointer to the next item
		cout << *p << endl;
	// writes 10 20 30, one per line 


	list<double> ld(10);
	// ld.size() is 10, each element is 0.0
	list<string> ls(10, "Hello");
	// ls.size() is 10, each element is "Hello"
	vector<string> vs(ls.begin(), ls.end());
	// vs.size() is 10, vs[0] is "Hello", vs[1]
	// is "Hello", ..., vs[9] is "Hello"
	list<int>::iterator p = li.end();
	p--;
	p--;
	// p -= 2 won't compile

	// li.begin()	p		li.end()
	// v			v		v
	// 10			20		30
	list<int>::iterator q = li.insert(p, 40);
		// inserts 40 at position q right before position b
	// li.begin()		q		p		li.end()
	// v				v		v		v
	// 10				40		20		30

	list<int>::iterator p;
	...;
	// li.begin()	p		li.end()
	// v			v		v
	// 10			20		30
	list<int>::iterator q = li.erase(p); // p is deleted and erase returns the iterator pointer to the element after p
	// li.begin()	q	li.end()
	// V			v	v
	// 10			30
	
	//It's now undefined to use p (*p, p++, etc.) until you assign p a new value


	// vectors also have iterators
	vector<int> vi;
	...;
	vector<int>::iterator p = vi.end() – 2; // for a vector, we can go forward or backward on our iterator by any amount; we're not constrained to using ++ and --
	// vi.begin()	p	vi.end()
	// v			v	v
	// 10			20	30
	vector<int>::iterator q = vi.insert(p, 40); // inserts 40 at position of p, pushes everything to the back
	// vi.begin()	q		vi.end()
	// v			v		v
	// 10			40	20	30
	// It's now undefined to use p (*p, p++, etc.) until you assign p a new value
	
	p = vi.erase(q);
	// vi.begin()	p	vi.end()
	// v			v	v
	// 10			20	30
	// It's now undefined to use q (*q, q++, etc.) until you assign q a new value
}

// #########################################################################################################
#include <set>
	// a set is a container without duplicates or order
	// we can ask whether an element is contained in the set - the set will check efficiently

int main() {
	set<string> s; // empty set of strings
		// no push back or push front, since there is no order in a set
	s.insert("Fred");
	s.insert("Ethel");
	s.insert("Fred"); // "Fred" already there, and therefore not added
	cout << s.size(); // size is 2
	s.erase("Ethel");
	s.insert("Desi");

	// iterating over a se
	for (set<string>::iterator p = s.begin(); p != s.end(); p++)
		cout << *p << endl;

	// s.find() gives us an iterator to the object in the set; if the object is not in the set, it returns s.end()
	if (s.find("Fred") != s.end())
		cout << "Found Fred!" << endl;
}

// #########################################################################################################
template<typename Iter, typename T>
Iter find(Iter b, Iter e, const T& target) {
	// general find algorithm that can be applied to almost any container containing any type that supports == comparison
	for (; b != e; b++)
		if (*b == target)
			break;
	return b;
}

int main() {
	int a[5] = { 10, 50, 40, 20, 30 };
	...;
	int* p = find(a, a + 5, k);
	if (p == a + 5)
		... not found ...;
	else
		... found, p points to the first element with that value;
	list<string> ls;
	...
	list<string>::iterator q = find(ls.begin(), ls.end(), "Fred");
	if (q == ls.end())
		... not found ...;
	...;
	vector<int> vi;
	...;
	vector<int>::iterator r = find(vi.begin(), vi.begin() + 5, 42);
	if (r == vi.begin() + 5)
		... not found ...
}