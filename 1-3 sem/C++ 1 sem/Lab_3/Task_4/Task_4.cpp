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
	int sum = 0;
	cout << "This program calculates the sum of even numbers in the range from 1 to n" << endl;
	
	cout << "enter number n: ";

	int n = getint();

	for (int i = 1; i <= n; i++) {
		if (i % 2 == 0) {
			sum += i;
		}
	}

	cout << "sum of even numbers less than n is: " << sum << endl;

	return 0;
}