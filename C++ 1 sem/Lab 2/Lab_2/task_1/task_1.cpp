#include <iostream>

using namespace std;

int main() {

	int a, b;

	cout << "enter number 1: ";
	cin >> a;
	cout << endl << "enter number 2: ";
	cin >> b;

	if (a % b == 0) {
		cout << "The first number can be diveded by the second number without remainder";
	}
	else if (b % a == 0) {
		cout << "The second number can be diveded by the first number without remainder";
	}
	else {
		cout << "nothing can be divided without remainder";
	}

	return 0;
}