#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double W, H, x1, y1, x2, y2, w, h, a, b, c, d, r;

	cout << "enter side W: ";
	cin >> W;
	if (W < 1) {
		cout << endl << "enter side W: ";
		cin >> W;
	}

	cout << "enter side H: ";
	cin >> H;
	if (H > 108 || H < 1) {
		cout << endl << "enter side H: ";
		cin >> H;
	}

	cout << "enter coordinate x1: ";
	cin >> x1;
	cout << "enter coordinate y1: ";
	cin >> y1;
	cout << "enter coordinate x2: ";
	cin >> x2;
	cout << "enter coordinate y2: ";
	cin >> y2;
	if (x1 < 0 || x2 < x1 || x2 > W || y1 < 0 || y2 < y1 || y2 > H) {
		cout << endl << "enter coordinate x1: ";
		cin >> x1;
		cout << endl << "enter coordinate y1: ";
		cin >> y1;
		cout << endl << "enter coordinate x2: ";
		cin >> x2;
		cout << endl << "enter coordinate y2: ";
		cin >> y2;
	}

	cout << "enter side w: ";
	cin >> w;
	if (w < 1 || w > W) {
		cout << endl << "enter side w: ";
		cin >> w;
	}

	cout << endl << "enter side h: ";
	cin >> h;
	if (h < 1 || h > H) {
		cout << endl << "enter side h: ";
		cin >> h;
	}
	a = x1;									//calculating free space around the table ¹1
	b = W - x2;
	c = H - y2;
	d = y1;
	if (c + d < h && a + b < w) {			// not enough space
		cout << -1;
	}

	else if (a >= w || b >= w) {	//more space then we need
		cout << 0;
	}

	else if ((a < w && b < w) && (a + b >= w)) {			// not enough space right and left but in sum enough
		if (a > b) {
			cout << w - a;
		}
		else if (b > a) {
			cout << w - b;
		}
		else {
			cout << w - b;
		}
	}

	else if ((a < w && b < w) && (a + b == w)) {		//not enough space but sum is equal to width
		if (a > b) {
			cout << b;
		}
		else if (b > a) {
			cout << a;
		}
		else {
			cout << b;
		}
	}

	else if ((d >= h || c >= h) && (W >= w)) {		//enough space under table ¹1
		cout << 0;
	}

	else if (w < W && d < h && c < h && d + c >= h && a + b < w) {
		if (c > d) {
			cout << h - c;
		}
		else if (c < d) {
			cout << h - d;
		}
		else {
			cout << h - d;
		}
	}
	return 0;
}