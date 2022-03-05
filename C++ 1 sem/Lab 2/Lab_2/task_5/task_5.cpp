#include <iostream>

using namespace std;

int main() {

	double a, b, c, d, z;

	cout << "enter number a: ";
	cin >> a;
	cout << "enter number b: ";
	cin >> b;
	cout << "enter number c: ";
	cin >> c;
	cout << endl << "enter number d: ";
	cin >> d;

	if (c >= d && a < d) {
		z = a + b / c;
	}
	else if (c < d && a >= d) {
		z = a - b / c;
	}
	else {
		z = 0;
	}

	cout << endl << z;

	return 0;
}