#include <iostream>

using namespace std;

int main() {

	double e = 2.178, x, a, b, pi = 3.1415, lnx, c, d, f, k, sin1 = 0, sin2 = 0, p = 0, o, v = 0, z = 0;
	int i = 0, j = 0;
	cout << "enter number x: ";
	cin >> x;
	a = ((x * 180) / pi);
	b = (int)a % 360;
	c = pi * b / 180;
	c = p;

	if (x >= e || x <= -e) {
		if ((b > 225 && b < 360) || (b >= 0 && b <= 45)) {
			while (i < 10) {
				f = 1;
				d = c / f;
				sin1 = sin1 + d;
				i++;
				f = f * (f + 1) * (f + 2);
				c = c * p * p;
			}
			while (j < 10, v = c * c * c) {
				
				k = 1;
				o = v / z;
				sin2 = sin1 + o;
				j++;
				z = z * (z + 1) * (z + 2);
				v = v * p * p;
			}
			cout << "sin(x) is the lowest and sin = " << sin1;
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