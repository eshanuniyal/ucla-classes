#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

double compute_mean(int a[], int n); // when taking an array a as a parameter, syntax: <type> a[]
void set_all(int b[], int n, int value); // function to set all values of an array to a particular value

int main() {
	// writing a program to find the mean of an unspecified number of input integers

	int total; // the total of the scores
	int n_scores = 0; // the total number of scores

	cout << "Enter the scores line by line below (negative when done): "

		while true{
			int s;
			cin >> s;

			if (s < 0)
				break;

			total += s; // adding to total
			n_scores++; // incremementing number of scores
		}

	if (n_scores == 0) // if we don't handle this case, we may get an undefined behaviour error (dividing by zero)
		cout << "There were no scores, so no average" << endl;
	else
		cout << "The average of all the scores is " << static_cast<double>(total) / n_scores << endl;
			// here, the static_cast function changes temporarily changes the type of total
			// syntax: static_cast<destination type>(source expression);

	// -----------------------------------------------------------------------------
	// writing a program to compute the mean and standard deviation of an unspecified number of scores
		// we already have a program to compute the mean; however, we're discarding the scores there
		// to compute the standard deviation, we need to save the scores --> use an array

	int n_scores = 0; // the total number of scores

	// in C++, the compiler needs to know how many values the array is supposed to handle when it's declared
	const int max_scores = 10000;
	int scores[max_scores]; // array to stoore scores

	cout << "Enter the scores line by line below (negative when done): "

		while true{
			int s;
			cin >> s;

			if (s < 0)
				break;
			if (n_scores == max_scores) {
				cout << "Cannot handle more than " << max_scores << " entries; your last stored entry is " 
					<< scores[n_scores - 1] << "." << endl;
				cout << "Continuing with just the " << max_scores << " values." << endl;
				break;
			}

			scores[n_scores] = s;
			n_scores++; // incremementing number of scores
		}
	
	if (n_scores == 0) // if we don't handle this case, we may get an undefined behaviour error (dividing by zero)
		cout << "There were no scores, so no statistics" << endl;
	else {
		
		double mean = compute_mean(scores, n_scores);
		
		double sum_of_squares = 0; // sum of squares of deviations from the mean
		for (int i = 0; i < n_scores; i++){
			double diff = scores[i] - mean;
			double sum_of_squares += diff * diff;
		}



		double standard_dev = sqrt(sum_of_scores / n_scores);

		cout << "The average of all the scores is " << mean << "." << endl;
	}
}

double compute_mean(const int a[], int n) {
	// note that passing an array into a function does /not/ copy the array; it's kind of like passing-by-reference
	
	a[0] = 42; // won't compile, since array was passed in as constant
	set_all(a, n, 42); // won't compile, since set_all modifies the array and it was passed in as a constant in compute_mean
	
	if (n <= 0)
		return 0; // if no items or invalid number of items, return 0

	int total = 0;
	for (int k = 0; k < n; k++)
		total += a[k];
	return total / n;
}

void set_all(int b[], int n, int value) {
	for (int i = 0; i < n; i++)
		b[i] = value;
}
