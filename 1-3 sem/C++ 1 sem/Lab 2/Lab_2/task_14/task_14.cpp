#include <iostream>

using namespace std;

int main() {

	double a, b, c, x, y;

	cout << "enter side a: ";
	cin >> a;
	cout << "enter side b: ";
	cin >> b;
	cout << "enter side c: ";
	cin >> c;
	cout << "enter side x: ";
	cin >> x;
	cout << "enter side y: ";
	cin >> y;


	if (a <= x && b <= y) {
		cout << "it wil go inside";
	}else if (a <= y && b <= x) {
		cout << "it wil go inside";
	}
	else if (c <= x && a <= y) {
		cout << "it wil go inside";
	}
	else if (c <= y && a <= x) {
		cout << "it wil go inside";
	}
	else if (c <= y && b <= x) {
		cout << "it wil go inside";
	}
	else if (c <= x && b <= y) {
		cout << "it wil go inside";
	}
	else {
		cout << "can't go in";
	}
	return 0;
}