bool anyFalse(const double a[], int n) {
	// no elements left -> somePredicate returns true for all elements -> return false
	// Return true if the somePredicate function returns false for at least one of the array elements; 
		// return false otherwise.
	if (n <= 0)
		return false;

	// if somePredicate returns false for first element, return true
	if (!somePredicate(a[0]))
		return true;
	// somePredicate returns true on first element; checking somePredicate for next element 
		// (n - 1 elements in array starting with second element)
	else return anyFalse(a + 1, n - 1);
}

int countTrue(const double a[], int n) {
	//  Return the number of elements in the array for which the somePredicate function returns true.	
	
	// no elements -> somePredicate doesn't return true for any elements -> return 0
	if (n <= 0)
		return 0;

	// return total number of elements for which somePredicate returns true
	return somePredicate(a[0]) + countTrue(a + 1, n - 1);
		// equals number of elements after current element for which somePredicate returns true, plus one if somePredicate returns true for current element
		// somePredicate(a[0]) is true (1) or false (0)
}

int firstTrue(const double a[], int n) {
	// Return the subscript of the first element in the array for which the somePredicate function returns true.  
	// If there is no such element, return -1.

	// no elements left -> no elements for which somePredicate returns true -> return -1
	if (n <= 0)
		return -1;

	// if somePredicate returns true for first element, return 0
	if (somePredicate(a[0]))
		return 0;

	// somePredicate doesn't return true on first element; check somePredicate for rest of the array 
	int first_index = firstTrue(a + 1, n - 1); // either -1 or index of desired element in subarray
	
	if (first_index == -1) // found no elements for which somePredicate returns true
		return -1;
	// element for which somePredicate returns true found, and its index (in subarray) stored in first_index
	else return 1 + first_index;
		// we add 1 to make sure we're returning the real index of the element, not its index in the (a-1)-length subarray
}

	
int positionOfSmallest(const double a[], int n) { // { 1, 3, 2 } 
	// Return the subscript of the smallest element in the array (i.e., return the smallest subscript m such that a[m] <= a[k] for all  k from 0 to n-1).
	// If the function is told to examine no elements, return -1.

	// asked to examine no elements
	if (n <= 0)
		return -1;

	// assuming first element is smallest
	int smallest_index = 0;
	double smallest = a[0];
	
	int next_smallest_index = positionOfSmallest(a + 1, n - 1);
		// index of smallest element in subarray; -1 if subarray empty

	// subarray after current element not empty, and smallest element in subarray smaller than current smallest
	if (next_smallest_index != -1 && a[next_smallest_index + 1] < smallest) {
		// updating smallest_index and smallest
		smallest_index = next_smallest_index + 1;
		smallest = a[next_smallest_index];
	}

	return smallest_index;
}
bool contains(const double a1[], int n1, const double a2[], int n2) {
	// If all n2 elements of a2 appear in the n1 element array a1, in the same order (though not necessarily consecutively), then return true; 
	// otherwise (i.e., if the array a1 does not contain a2 as a not-necessarily-contiguous subsequence), return false.

	// first array exhausted, or first array smaller than second array -> elements not found
		// we don't test for n1 <= 0, since we return true when n1 == n2 == 0 (both arrays run out)
	if (n1 < 0 || n1 < n2)
		return false;

	// second array empty
	if (n2 <= 0)
		return true;

	// current element of a2 found in a1
	if (a2[0] == a1[0]) {

		// search for subarray of a2 in subarray of a1
		if (contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1))
			return true;
		else
			return false;
	}
	// current element of a2 not found in a1
	else {

		// search for a2 in subarray of a1
		if (contains(a1 + 1, n1 - 1, a2, n2))
			return true;
		else
			return false;
	}
}