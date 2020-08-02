/* Different sorting algorithms
	- O(N^2):
		- Selection sort: absolutely horrible
		- Bubble sort: not great
		- Insertion sort: relatively quick and easy to implement
	- O(NlogN) -> theoretically fastest order of time for sorting elements with comparisons involved
		- Merge sort: worst and average are both O(NlogN)
		- Quick sort
*/

// Quicksort 
	// First, we need to pick a pivot roughly between the extremes of the data, i.e. a pivot close to a median
	// We usually pick the first, the last and the middle element in the array, and take their median to be the median of the entire array
		// This works for all kinds of data - notably, it works better than anything else for data that's already nearly sorted in some order, 
		// and works as well as anything else for random data

// Let's take median 5 for the following data
5 3 7 6 1 8 2 4		// we take pointers from both ends, and swap any elements we encounter that should be on opposite ends
5 3 4 2 1 8 6 7 	// we swapped 4 and 7, and 2 and 6
	// we then put 5 in the middle
3 4 2 1 5 8 6 7
	// and sort each half
1 3 4 2		// if we take median 1 for the left half, we see it's already split appropriately
  3 4 2		// 2 is larger than 3, so we swap and put 3 in the middle
  2   4
  ...

// One optimisation is to use 2 items as a base case rather than the trivial case of 1 item; 
  	// as soon as we encounter a set of 2 items, we just compare and sort them if they're out of order

#include <algorithm>
int main(){
	vector<int> v;
	sort(v.begin(), v.end()); 		// implements a modified quick sort algorithm to sort the vector
		// since quicksort relies on random access, it only works for vectors and arrays; not lists
	sort(v.begin(), v.end(), comparison_function);	// we can also pass in a comparison function for the sort function to use, instead of the default < operator

	// sorting lists
	list<int> li;
	li.sort();		// a member function that sorts the list using merge sort

	list<Employee> le;
	le.sort(makesMoreThan);	// a member function that sorts le based on who makes more
}

// quicksort is generally faster than merge sort, but there are some cases where merge sort could be faster
	// e.g. when items are expensive to copy or move around
	// in this case, sorting elements in a linked list may be much easier, since we don't need to copy or move any items; we can just exchange or work with the pointers
// since lists use an implementation of merge sort as a member function, the sort function can access private data members of the list
	// it's therefore faster than a non-member function sort function that would copy and move the actual objects

// alternate implementation of quicksort: introsort
	// modification: the quick sort tracks how deep the recursion is going
		// if the recursion is going too deep, then we're likely dealing with a worst case quicksort i.e. O(N^2)
		// it then switches, at that level of recursion, to mergesort (which has worst case O(NlogN))

// Making decisions about sorting data
// 1. Check if the environment has a sort function and use that
// 2. If the environment doesn't provide a sort function, implement a quicksort, merge sort or insertion sort (or some modified version or combination of those)
	// depending on what works

// Looking up and inserting/erasing
/*					Lookup		Insert/Erase
Unsorted vector 	O(N)		O(1) if duplicates allowed; O(N) otherwise
Sorted vector 		O(logN)		O(N)
Unsorted list 		O(N)		O(N)
Sorted list 		O(N)		O(N)

- Unsorted vector insert/erase will take O(N) if duplicates aren't allowed because we'll first need to do a lookup to check whether the element is already in the vector
- Sorted vector lookup takes O(logN) steps because we can ask whether an element is greater than or less than the median maximum log(base 2) of N times to find the element
- Sorted vector insert/erase will take O(N) since, on average, half the elements will need to be moved down the vector
- Unsorted list lookup and inserting/erasing will both take O(N) since we'll need to traverse the nodes sequentially to find the element / insert one at the right position / delete it
- The same goes for the sorted list, albeit a bit faster
*/

/* HASH TABLES
- "Bucket": an element in an array representing a container of items that correspond to the index/key of that element
- Load factor = total number of items / number of buckets
- "Collision" - a situation when multiple items correspond to the same key

						Lookup 		Insert/Erase
Hash table (fixed #)	O(N)

- Lookup is order N because when we double the number of elements, we double the load factor and therefor double the lookup time through the linked list each bucket represents
- Why is hash table then better than a sorted vector, which is O(logN)?
	- When we look at the proportionality constant, we see that, say, a hash table with 10k buckets has proportionality constant 1/10K * N
	- A sorted vector, on the other hand, is going to be log(base2)N
	- For a large enough N, the hash table is going to be worse than a binary search algorithm
	- For smaller (and typically more practical sizes of) N, the hash table is much faster

When actually implementing a hash table for, say, UCLA students' student ID numbers, we see that we get much worse performance than expected; why?
	- UCLA student ID numbers are not a random distribution; many are in the format x048xxxxx ... x053xxxxx
	- The first digit is actually a check digit, computed from the rest
	- most people at UCLA are gonna fall into one of sixty buckets, if we're creating buckets based on the first 4 digits; 
		we'll then have 40k/60 students per bucket, resulting in a pretty slow lookup
You therefore need to make sure that the algorithm you're using to generate the bucket key creates a random distribution e.g. the /last/ 4 digits of the UID
*/