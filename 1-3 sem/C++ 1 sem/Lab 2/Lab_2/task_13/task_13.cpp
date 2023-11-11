#include <iostream>
#include <cmath>

using namespace std;

int main() {

	double a, R, r, angle_in_rad, pi = 3.1415, s;
	int q;

	cout << "enter side P: ";
	cin >> a;
	cout << "enter angle Q(in degrees): ";
	cin >> q;
	cout << "enter radius R: ";
	cin >> R;
	angle_in_rad = (q * pi) / 180;
	s = (a * a * sin(angle_in_rad));
	r = ceil((s / (2 * a)) * 10000) / 10000;

	if (r >= R) {
		cout << "Sphere will go in";
	}else {
		cout << "Sphere cant go in";
	}

	return 0;
}