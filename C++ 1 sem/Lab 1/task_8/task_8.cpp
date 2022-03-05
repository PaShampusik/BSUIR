#include <iostream>

using namespace std;

int main() {
	double a, a100, d, S;
	const int n = 40;
	cout << "enter a: ";
	cin >> a;
	cout << "enter a100: ";
	cin >> a100;
	d = (a100 - a) / 99;
	S = ((2 * a + d * (n - 1)) / 2) * n;
	cout << "difference = " << d << endl;
	cout << "sum = " << S << endl;
	return 0;
}