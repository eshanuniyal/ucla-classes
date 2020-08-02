#include <iostream>
#include <string>
using namespace std;

int main() {
	string* fp;
	string fish[5];
	fp = &fish[4];
	* fp = "yellowtail";
	* (fish + 3) = "salmon";
	fp = fp - 3;
	fp[1] = "sole";
	fp[0] = "eel";
	bool d = (fp == fish);
	bool b = (*fp == *(fp + 1));

	for (int i = 0; i != 5; i++)
		cout << fish[i] << " ";
	cout << endl;
}