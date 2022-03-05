#include <iostream>

using namespace std;

int main() {

	double e = 2.178, x, a, b, pi = 3.1415, lnx, c;

	cout << "enter number x: ";
	cin >> x;
	a = ((x * 180) / pi);
	b = (int)a % 360;
	c = pi * b / 180;
	if (x >= e || x <= -e) {
		if ((b > 225 && b < 360) || (b >= 0 && b <= 45)) {
			cout << "sin(x) is the lowest and sin = " << c - (c * c * c) / (2 * 3) + (c * c * c * c * c) / (2 * 3 * 4 * 5) - (c * c * c * c * c * c * c) / (2 * 3 * 4 * 5 * 6 * 7) + (c * c * c * c * c * c * c * c * c) / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9) - (c * c * c * c * c * c * c * c * c * c * c) / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11) + (c * c * c * c * c * c * c * c * c * c * c * c * c) / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13);
		}
		else {
			cout << "cos(x) is the lowest and cos = " << 1 - (x * x) / 2 + (x * x * x * x) / (2 * 3 * 4) - (x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6) + (x * x * x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6 * 7 * 8) - (x * x * x * x * x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10) + (x * x * x * x * x * x * x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);

		}
	}
	else if (x <= 1.3 && x >= -1.3) {
		cout << "ln|x| is the lowest";
		if (x < 0) {
			x = -x;
		}
		else { x = x; }
		lnx = (x - 1) - ((x - 1) * (x - 1)) / 2 + ((x - 1) * (x - 1) * (x - 1)) / 3 - ((x - 1) * (x - 1) * (x - 1) * (x - 1)) / 4 + ((x - 1) * (x - 1) * (x - 1) * (x - 1) * (x - 1)) / 5;
			cout << lnx;
	}
	else if ((x > 1.3 && x < e) || (x < -1.3 && x > -e)) {
		cout << "cos(x) is the lowest and cos = " << 1 - (x * x) / 2 + (x * x * x * x) / (2 * 3 * 4) - (x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6) + (x * x * x * x * x * x * x * x) / (2 * 3 * 4 * 5 * 6 * 7 * 8);

	}
		return 0;
		}
	