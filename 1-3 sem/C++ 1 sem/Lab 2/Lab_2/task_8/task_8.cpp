#include <iostream>
#include <cmath>

using namespace std;

int main() {

	double z, a, d, x, f, y;
	int n;


	cout << "if n = 1, f(x) = 2x" << endl << "if n = 2, f(x) = x^3" << endl << "if n = 3, f(x) = x/3" << endl << endl;
	cout << "enter number n: ";
	cin >> n;
	cout << "enter number z: ";
	cin >> z;
	cout << "enter number a: ";
	cin >> a;
	cout << "enter number d: ";
	cin >> d;


	if (z > 0) {
		x = -3 * z;
	}
	else {
		x = z * z;
	}


	switch (n) {
		case 1:
			f = 2 * x;
			cout << "using f = 2x";
			break;
		case 2:
			f = x * x * x;
			cout << "using f = x^3";
			break;
		case 3:
			f = x / 3;
			cout << "using f = x / 3";
			break;
	}

	y = 2 * f * (a * sin(x) + d * exp(-x - 3));
	cout << endl << "y = " << y;

	return 0;
}