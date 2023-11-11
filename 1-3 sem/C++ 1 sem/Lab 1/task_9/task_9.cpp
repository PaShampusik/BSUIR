#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double b1, n = 30, N, q;
	cout << "enter b1: ";
	cin >> b1;
	q = 1 / (n + 1);
	N = fabs(round(b1 / (1 - q)));
	cout << endl << "number of members = " << N;
	return 0;
}