#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "enter n = 1, if you want to solve with logical variable\nenter n = 2, if you want to solve without logical variable\n";
	cin >> n;
	switch (n) {
	case 1:
		double a, b;
		cout << "enter number a: ";
		cin >> a;
		cout << endl << "enter number b: ";
		cin >> b;
		a > b ? cout << "a is bigger then b" : a == b ? cout << "a is equal to b" : cout << "b is bigger then a";
		break;
	case 2:
		double x, y;
		bool d;
		cout << "enter number a: ";
		cin >> x;
		cout << endl << "enter number b: ";
		cin >> y;
		d = x > y;
		d ? cout << "x is bigger then y" : x == y ? cout << "x is equal to y" : cout << "x is bigger then y";
		break;
	}
			return 0;
	return 0;
}