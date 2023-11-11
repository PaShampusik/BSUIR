#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double t, a, v, t1, t2, r;
	cout << "enter speed: " << endl;
	cin >> v;
	cout << "enter time: " << endl;
	cin >> t;

	while (t < 0) {
		cout << "enter time: " << endl;
		cin >> t;
	}
	cout << "enter aceleration: " << endl;

	cin >> a;
	t1 = fabs(v / a);
	t2 = t - t1;

	if ((v >= 0 && a >= 0) || (v <= 0 && a <= 0)) {		//if we have no stop moment
		r = fabs(v * t + ((a * t * t) / 2));
	}
	else {				//if we have stop moment
		r = fabs(v * t1 + (a * t1 * t1) / 2) + fabs(a * t2 * t2 / 2);
	}
	cout << r;
	return 0;
}