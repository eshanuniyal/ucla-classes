#include <iostream>

using namespace std;

void deleteG(char* arr) {

	// running through array to check for g's
	while (*arr != 0) {

		// checking if current character is a g
		if (tolower(*arr) == 'g') {

			// moving all characters after current character to the left
			char* current_ptr = arr; // stores pointer to element current index

			// while current element is not zero byte
			while (*current_ptr != 0) {
				*current_ptr = *(current_ptr + 1); // move next element left
				current_ptr++; // incremenet current_ptr
			}
		}
		arr++; // incremenet arr
	}
}

int main()
{
	char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
	deleteG(msg);
	cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
}