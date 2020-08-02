# include <iostream>

using namespace std;

// code without pointers
int findFirstNegative(double a[], int n) {

	for (int k = 0; k < n; k++)
		if (a[k] < 0)
			return k;
	return -1;
}

// code with pointers
double* findFirstNegative(double a[], int n) {
	// code using pointers
	for (double* dp = a; dp < a + n; dp++)
		if (*dp < 0)
			// returning index of *dp
			return dp - a; // dp is the pointer of the element, and a is the pointer of the first element
				// dp - a therefore returns the difference in their indices 
				// (converted automatically from the difference in their addresses)
	return a + n;
	// or, could just return the null pointer value (much better)
		// the null pointer value doesn't point to any object, and it is illegal to follow
		// it can only be assigned to a pointer variable or compared to a pointer variable
	return nullptr;
}

int main() {
	const int maxSize = 5;
	double da[MAXSIZE]; // array da with MAXSIZE elements
	double* dp; // declaring a pointer dp that point sto a double

	for (int k = 0; k != MAXSIZE; k++)
		da[k] = 3.6;

	for (dp = &da[0]; dp != &da[MAXSIZE]; dp++)
		// dp++ moves to the pointer to the next element in the array
			// if dp was at address 1000, adding one moves us to address 1008 
			// (we advanced one double, equivalent to 8 bytes)
		// rule: &a[i] + j = &a[i + j]
		// &da[MAXSIZE] is a valid call --> we can generate a pointer to a location just outside of the array
			// however, we cannot follow that pointer --> *&da[5] is invalid
		// we can also make the comparison != between pointers
			// &da[i] != &da[j} <---> i != j
			// &da[i] == &da[j} <---> i == j
		// within an array:
			// &da[i] op &da[j} <---> i op j (where op may be <, >, <=, <=, ==, !=)
		* dp = 3.6; // current value of dp is &da[0]
			// therefore, * dp = * (&da[0]) = da[0]
			// therefore, da[0] is set to 3.6

	// we may write the above loop as
	for (dp = da; dp != da + MAXSIZE; da++)
		// Assigning da to a pointer (dp, double pointer) is equivalent to 
			// assigning the location of the first element of da (&da[0]) to the pointer
		* dp = 3.6;

	// when we pass an array as a parameter into a function, 
		// what we're really passing is a pointer for the first element of that array
	// e.g. passing in array da is equivalent to passing in &da[0]
	// when we call da[i], what we're really calling is 
		// * (da + i) = * (&da[0] + i) = * (&da[0 + i]) = * &da[i] = da[i]

	// passing an array into a function that doesn't start at index 0
	string sa[5] = { "rat", "mouse", "dog", "cat", "bird" };

	int m = detectMatch(&sa[1], 3, "cat");
	int m = detectMatch(sa + 1, 3, "cat"); // these two statements are equivalent
		// within the function, sa[1] will be considered sa[0] and so on
		// m will therefore return 2, even though "cat" is at index 3 in the actual string
	

	// working with arrays without pointers
	double da[5];
	int fnpos = findFirstNegative(da, 5);
	if (fnpos == -1)
		cout << "There are no negative values in the array." << endl;
	else {
		cout << "The first negative value is at position " << fnpos << endl;
		cout << "Its value is " << da[fnpos] << endl;
	}

	// working with pointers
	double da[5];
	double* fnptr = findFirstNegative(da, 5);
	if (fnptr == nullptr)
		cout << "There are no negative values in the array." << endl;
	else {
		cout << "The first negative value is at position " << fnptr - da << endl;
		cout << "Its value is " << *fnptr << endl;
	}
}