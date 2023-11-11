#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int i = 0;
	double d, sum = 0;
	do {
		d = pow(1 / 2.0, i) + pow(1 / 3.0, i);
		sum += d;
		i++;
	} while (d > 0.001);
	cout << "sum is " << sum;
	return 0;
}