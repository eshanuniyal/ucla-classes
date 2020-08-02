#include <iostream>

using namespace std;

// return true if two C strings are equal
bool match(const char str1[], const char str2[])
{
	const char* str1_p = &str1[0];
	const char* str2_p = &str2[0];

	while (*str1_p != 0 && *str2_p != 0)  // zero bytes at ends
	{
		if (*str1_p != *str2_p)  // compare corresponding characters
			return false;
		str1_p++;            // advance to the next character
		str2_p++;
	}
	return *str1_p == *str2_p;   // both ended at same time?
}

int main()
{
	char a[10] = "pointy";
	char b[10] = "pointless";

	if (match(a, b))
		cout << "They're the same!\n";
}
