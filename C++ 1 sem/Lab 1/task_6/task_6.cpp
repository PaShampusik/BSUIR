#include <iostream>

using namespace std;

int main() {
	int h1, h2, m1, m2, h, m;
	cout << "enter hours(first case): ";
	cin >> h1;
	while ((h1 < 0) || (h1 > 23)) {
		cout << endl << "enter hours(first case): ";
		cin >> h1;
	}
	cout << endl << "enter minutes(first case): ";
	cin >> m1;
	while (m1 < 0 || m1 > 59) {
		cout << endl << "enter minutes(first case): ";
		cin >> m1;
	}
	cout << endl << "enter hours(second case): ";
	cin >> h2;
	while (h2 < 0 || h2 > 23) {
		cout << endl << "enter hours(second case): ";
		cin >> h2;
	}
	cout << endl <<"enter minutes(second case): ";
	cin >> m2;
	while (m2 < 0 || m2 > 59) {
		cout << endl << "enter minutes(second case): ";
		cin >> m2;
	}

	if (h2 > h1 && m2 >= m1) {
		h = h2 - h1;
		m = m2 - m1;
	}
	else if (h2 > h1 && m2 <= m1) {
		h = h2 - h1 - 1;
		m = 60 - (m1 - m2);
	}
	else if (h2 < h1 && m2 >= m1) {
		h = 24 - (h1 - h2);
		m = m2 - m1;
	}
	else if (h2 < h1 && m2 <= m1) {
		h = 24 - (h1 - h2) - 1;
		m = 60 - (m1 - m2);
	}

	if (h == 1) {				//language mistakes
		cout << h << " hour ";
	}
	else {
		cout << h << " hours ";
	}
	if (m == 1) {
		cout << m << " minute";
	}
	else {
		cout << m << " minutes";
	}
	return 0;
}