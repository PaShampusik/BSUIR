#include <iostream>
#include <cmath>

using namespace std;

int main() {

	int a, b, c, d, e, f, k, n = 1;
	cout << "given the program displays all numbers less than 10 to the 6th power for which it is true that the sum of a\
			ll digits of a number raised to a power that is equal to the number of digits is equal to the number itself";

	for (int i = 1; i < 1000000; i++) {

		k = i;

		while (k / 10 > 0) {
			k = k / 10;
			n++;
		}

		a = i / 100000;
		b = (i - 100000 * a) / 10000;
		c = (i - a * 100000 - b * 10000) / 1000;
		d = (i - a * 100000 - b * 10000 - c * 1000) / 100;
		e = (i - a * 100000 - b * 10000 - c * 1000 - 100 * d) / 10;
		f = i % 10;

		if ((pow(a, n) + pow(b, n) + pow(c, n) + pow(d, n) + pow(e, n) + pow(f, n)) == i) {
			cout << i << endl;
			
		}

		n = 1;
	}
	

	return 0;
}