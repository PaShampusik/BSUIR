#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>

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
	cout << "This program calculates the sum of even numbers in the range from 1 to n" << endl;
	int a;
	double sum1;
	int n = getint();
	a = n / 2;
	sum1 = 2 * a + a * (a - 1);
	cout << "sum of even numbers less than n is: " << sum1 << endl;
	return 0;
}	
