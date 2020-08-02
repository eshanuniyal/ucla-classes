#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

void removeOdds(list<int>& li);
void removeOdds(vector<int>& v);
void test1();
void test2();

int main()
{
	test1();
	test2();
	cout << "Passed" << endl;
}


// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not the same as in the original list.
void removeOdds(list<int>& li) {
	// iterating over list of ints
	for (list<int>::iterator i = li.begin(); i != li.end();) {
		// checking if element is odd
		if (*i % 2 == 1)
			i = li.erase(i); // when we erase element, i will be invalidated; 
				// we therefore update i to point to the element immediately after the element deleted (the iterator for which is returned by .erase())
		else
			i++;
	}
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not the same as in the original vector.
void removeOdds(vector<int>& v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ) {
		if (*it % 2 == 1)
			it = v.erase(it);
		else
			it++;
	}
}

void test1() {
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end());  // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

void test2()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}
