#include <iostream>
#include <string> // library to use strings

using namespace std;

int main(){
	cout << "What is your name? ";
	string personsName;
	getline(cin, personsName); // function getline() used to get the full string from cin;
		// cin would only get the first word when dealing with strings

	cout << "How old are you? ";
	int age;
	cin >> age;
	// urgent problem here: if you read a number using cin, and then use getline to read a string (line 25), the getline won't read anything;
		// it'll only retrieve the newline character at the end of the cin, see that there's empty space behind it, discard the newline character and store an empty string
		// on the other hand, a getline followed by a getline causes no issues;
			// the first getline extracts the full string from memory, including the newline character (which cin does not extract)
	cin.ignore(10000, '\n'); // ignores the newline character \n
			// this is not necessary in Visual Studio's compiler, but g++ may cause issues

	cout << "What is your quest? ";
	string quest;
	getline(cin, quest);

	// printing output
	cout << "Hello, brave " << personsName << "!" << endl;
	cout << "You want " << quest << endl;
	cout << "If you live, next year you will be " << age + 1 << endl;
}
