#include <iostream>
#include <cmath>

using namespace std;

int main() {

	
	int n;
	cout << "if you want so solve ax^4 + bx^2 + c = 0  ====>  enter n = 1\nif you want so solve ax^4 + bx^3 + cx^2 + bx + a = 0  ====>  enter n = 2\nif you want so solve x^3 + px + q = 0  ====>  enter n = 3\n";
	cout << "enter number n: ";
	cin >> n;
	switch (n) {

	case 1:													//case 1
		double a, b, c, d, t1, t2, x1, x2;
		cout << "enter number a: ";
		cin >> a;
		cout << "enter number b: ";
		cin >> b;
		cout << "enter number c: ";
		cin >> c;

		d = b * b - 4 * a * c;

		if (d > 0) {
			t1 = (-b + sqrt(d)) / (2 * a);
			t2 = (-b - sqrt(d)) / (2 * a);

			if (t2 < 0 && t1 >= 0) {
				x1 = sqrt(t1);
				x2 = -sqrt(t1);
				cout << "x1 = " << x1 << " " << "x2 = " << x2;
			}

			else if (t2 >= 0 && t1 >= 0) {
				double x3, x4;
				x1 = sqrt(t1);
				x2 = -sqrt(t1);
				x3 = sqrt(t2);
				x4 = -sqrt(t2);
				cout << "x1 = " << x1 << " " << "x2 = " << x2 << " " << "x3 = " << x3 << " " << "x4 = " << x4;
			}
			else {
				cout << "there is no answer";
			}
		}
		else if (d == 0) {
			double t;

			t = -b / (2 * a);
			if (t >= 0) {
				x1 = sqrt(t);
				x2 = -sqrt(t);
				cout << "x1 = " << x1 << " " << "x2 = " << x2;
			}
			else {
				cout << "there is no answer";
			}
		}
		else {
			cout << "there is no answer";
		}
		break;
	case 2:										//case 2
		double f, g, j, h, z1, z2, c1, c2, c3, c4;
		cout << "enter number a: ";
		cin >> f;
		cout << "enter number b: ";
		cin >> g;
		cout << "enter number c: ";
		cin >> j;

		h = g * g - 4 * f * (j - 2 * f);

		if (h > 0) {
			z1 = (-g + sqrt(h)) / (2 * f);
			z2 = (-g - sqrt(h)) / (2 * f);
			c1 = (z1 + sqrt(z1 * z1 - 4)) / 2;
			c2 = (z1 - sqrt(z1 * z1 - 4)) / 2;
			c3 = (z2 + sqrt(z2 * z2 - 4)) / 2;
			c4 = (z2 - sqrt(z2 * z2 - 4)) / 2;
			cout << "x1 = " << c1 << " x2 = " << c2 << " x3 = " << c3 << " x4 = " << c4;
		}
		else if (h == 0) {
			z1 = -g / (2 * f);
			c1 = (z1 + sqrt(z1 * z1 - 4)) / 2;
			c2 = (z1 - sqrt(z1 * z1 - 4)) / 2;
			cout << "x1 = " << c1 << " x2 = " << c2;
		}
		else {
			cout << "there is no answer";

		}
		break;
	case 3:											//case 3
		double q, o, e, k1, k2, k3, p, l1, l2 = 0, pi = 3.1415926;
		cout << "enter number p: ";
		cin >> p;
		cout << "enter number q: ";
		cin >> q;
		o = acos((-q) / 2 * (pow(3 / (-p), 1.5)));
		cout << o * 57;
		if (o > pi || o < 0) {
			cout << "no roots";
		}
		else {
			k1 = 2 * sqrt((-p) / 3) * cos(o / 3);
			k2 = 2 * sqrt((-p) / 3) * cos(o / 3 + (2 * pi) / 3);
			k3 = 2 * sqrt((-p) / 3) * cos(o / 3 - (2 * pi) / 3);
			cout << "x1 = " << k1 << " x2 = " << k2 << " x2 = " << k3;
		}
	}
	return 0;
}