#include <iostream>
#include <cmath>

using namespace std;

int main() {

	double x1, x2, y1, y2, r, R;

	cout << "enter coordinate x1: ";
	cin >> x1;
	cout << "enter coordinate y1: ";
	cin >> y1;
	cout << "enter radius r: ";
	cin >> r;
	cout << "enter coordinate x2: ";
	cin >> x2;
	cout << "enter coordinate y2: ";
	cin >> y2;
	cout << "enter radius R: ";
	cin >> R;

	double a;

	a = sqrt(pow(abs(x2 - x1), 2) + pow(abs(y2 - y1), 2));

	if (a == r + R) {
		cout << "The circles touch externally";
	}else if ((a > r && a < r + R) || ((a < r && a < r + R) && (a != 0))){
		cout << "The figures intersect";
	}else if (a < r && R < r - a) {
		cout << "Yes, but the opposite is true for two circles";
	}else if (a < R && r < R - a) {
		cout << "Yes";
	}else if (a = 0 && r > R) {
		cout << "Yes, but the opposite is true for two circles";
	}else if (a = 0 && R > r) {
		cout << "Yes";
	}else {
		cout << "Not a single condition is met";
	}

	return 0;
}