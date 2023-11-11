#include <iostream>
#include <cmath>

using namespace std;

double getdouble()
{
	double n;
	bool x = false;
	cin >> n;
	if (n < 0.1 || n > 1) {
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
		if (n < 0.1 || n > 1) {
			x = true;
		}
		else {
			x = false;
		}
	}return n;
}

int getint()
{
	double n;
	bool x = false;
	cin >> n;
	if (n - round(n) == 0) {

	}
	else {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(40000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> n;
		cout << endl;
		if (n - round(n) == 0) {
			x = false;
		}
		else {
			x = true;
		}
	}return n;
}

int main() {
	int n, j;
	double x, a, b, c, v, sum = 0, sum2;
	b = - 1;
	c = 1;
	v = -1;
	cout << "this program will calculate task through cicle and compare with frank cacuations" << endl\
		<< "enter number x (0.1 >= x <= 1) and number of members n (bigger than 0) for j different x" << endl;
	cout << endl << "enter number j: ";
	j = getint();

	do {
		cout << endl << "enter number n: ";
		n = getint();
	} while (n <= 0);
	for (int i = 0; i < j; i++) {
		do {
			cout << "enter number x: ";
			x = getdouble();
		} while (x < 0.1 || x > 1);

		for (int i = 1; i <= n; i++) {
			a = 2 * i * (2 * i - 1);
			c = c * x * x;
			v = v * b;
			sum += (c * v) / a;
		}
		sum2 = x * atan(x) - log(sqrt(1 + pow(x, 2)));
		cout << endl << sum << endl << sum2 << endl;
		if (fabs(sum2 - sum) <= 0.000001) {
			cout << "accuracy is enough" << endl;
		}
		else {
			cout << "accuracy is a little bit bad" << endl;
		}
	}
	return 0;
}