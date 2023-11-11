#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int a, b;
	for (int i = 11; i < 100; i++) {
		a = i / 10;
		b = i % 10;
		if (pow(a + b, 3) == pow(i, 2)) {
			cout << "a two-digit number with the property that the cube of \
the sum of its \ndigits is equal to the square of the number itself is " << i << endl;
			break;
		}
	}
	return 0;
}