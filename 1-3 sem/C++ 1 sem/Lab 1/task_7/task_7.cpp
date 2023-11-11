#include <iostream>

using namespace std;

int main() {
	int a, b;
	cout << "enter number a: ";
	cin >> a;
	cout << endl << "enter number b: ";
	cin >> b;
	cout << endl << "a = " << a << ", b = " << b << endl;
	a = a + b;
	cout << "a = " << a << ", b = " << b << endl;
	b = a - b;
	cout << "a = " << a << ", b = " << b << endl;
	a = a - b;
	cout << "a = " << a << ", b = " << b << endl;

	return 0;
}