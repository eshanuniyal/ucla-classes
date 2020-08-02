// #############################################################################################################

/* SORTING AN UNSORTED PILE INTO TWO PILES (continued)
	- Split the pile into two piles of N/2 items each
	- Sort the left pile
	- Sort the right pile
	- Merge the two sorted piles into one sorted pile

	If we apply the same algorithm to the two smaller piles to make things quicker, we have a *recursive solution*	

	if N > 1
		- Split the pile into two piles of N/2 items each
		- Sort the left pile
		- Sort the right pile
		- Merge the two sorted piles into one sorted pile
	else
		return pile

	With any recursive solution, we must be able to prove it terminates (which, in this case, we know is true because we terminate at N <= 1)
		and that it is does the correct thing (which, in this case, we can prove by induction)
*/

void sort(int a[], int b, int e) {
	// takes parameters array a, beginning index b, ending index e (which is just past the last index we actually look at)
	if (e - b > 1) { // if current size is strictly greater than one
		int mid = (b + e) / 2; // integer division gives midpoint
			// this particular algorithm (because it uses integer division) will split a pile with odd number of elements into a smaller left half and larger right half
		sort(a, b, mid); // sorting left half
		sort(a, mid, e); // sorting right half
		merge(a, b, mid, e);
	}
}

bool contains(const int a[], int n, int target) {
	// if first value is equal to target, we return true
	
	// if no elements left, no elements are equal to target -> return false
	if (n <= 0)
		return false;

	if (a[0] == target)
		return true;

	// if first value isn't target, we return whether or not the rest of the array has target
	else return contains(a + 1, n - 1, target);
}

bool solve(start, goal) {
	if (start == goal)
		return true;
	mark this position as visited;
	for each direction {
		if moving one step in that direction is possibleand that spot has not been visited{
			if solve((pos reached by moving that step, goal))
				return true;
		}
	}
	return false;
}