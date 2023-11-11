#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int i = 1, b;
	double a, sum = 0;
	while (i < 30) {
		if (i % 2 == 1) {
			a = i;
			b = i * i;
		}
		else {
			a = i / 2;
			b = i * i * i;
		}sum = sum + pow(a - b, 2);
		i++;
	}
	cout << "sum is " << sum;

	return 0;
}