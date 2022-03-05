#include <iostream>

using namespace std;

int main() {

	int a, b, c, d, e, k;
	cout << "number a is: ";
	cin >> a; 
	cout << "number b is: ";
	cin >> b;
	if (a > b) {
		c = a;
		d = b;
	}
	else {
		c = b;
		d = a;
	}

	while (c % d != 0)
	{
		e = c % d;
		c = d;
		d = e;
	}

	k = a * b / e;

	cout << "the greatest common divisor is: " << e << "\nthe smallest common multiple is: " << k;

	return 0;
}