#include <iostream>
#include <cmath>

using namespace std;

int getint()
{
	double n;
	bool x = false;
	cin >> n;
	if (n - round(n) != 0 || n < 0) {
		x = true;
	}
	else {
		x = false;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(40000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> n;
		cout << endl;
		if (n - round(n) != 0 || n < 0) {
			x = true;
		}
		else {
			x = false;
		}
	}return n;
}

int main() {

	cout << "this program will find approximately the root of the equation arccos(e)^(-(x-1)^2) + sin(x)" << endl;

	double x, n, h, min = 10000, minx = -5, y, e = 2.718281;

	do {
		cout << "enter number of steps n: " << endl;
		n = getint();
	} while (n <= 0 || n - n / 1 != 0);

	h = 4 / n;

	for (double i = -2; i <= 2; i += h) {

		y = acos(pow(e, -pow((i + 1), 2))) + sin(i);

		if (fabs(y) < min) {
			min = y;
			minx = i;
		}
	}

	cout << "x at which the value of the function tends to zero is equal to " << minx;
	return 0;
}