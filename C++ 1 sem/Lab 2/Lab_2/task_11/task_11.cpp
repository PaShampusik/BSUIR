#include <iostream>

using namespace std;

int main() {

	double a, r, pi = 3.1415, s_of_square, s_of_circle;

	cout << "enter side a: ";
	cin >> a;
	cout << "enter radius r: ";
	cin >> r;

	s_of_square = a * a;
	s_of_circle = pi * r * r;

	if (s_of_square > s_of_circle) {
		cout << "area of square is bigger";
	}else if (s_of_square < s_of_circle) {
		cout << "area of circle is bigger";
	}else {
		cout << "areas are equal";
	}

	return 0;
}