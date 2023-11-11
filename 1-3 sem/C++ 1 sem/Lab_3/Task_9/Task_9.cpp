#include <iostream>

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
	cout << "this proggram will caculate subsequence that looks like A0 - 2A1 + 4A2 - 8A3 + ... + 2^(n-1)-1^(n-1)A(n-1)" << endl;
	cout << "enter number of members n: ";

	int n = getint();

	double a, b = 1, c = 1, sum = 0;

	for (int i = 1; i <= n; i++) {
		cout << endl << "enter " << i << " member of subsequence: ";
		a = getint();
		a = b * c * a;
		sum += a;
		b *= 2;
		c *= -1;
	}

	cout << endl << "sum of " << n << " mebers is: " << sum;
	return 0;
}