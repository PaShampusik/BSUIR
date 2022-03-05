#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, c, y;

	cout << "enter number a: ";
	cin >> a;
	cout << "enter number b: ";
	cin >> b;
	cout << "enter number c: ";
	cin >> c;
	int n;
	cout << "enter number n: ";
	cin >> n;
	
	switch (n)
	{
	case 2:
		y = b * c - a * a;
		cout << "Y = " << y;
		break;
	case 56:
		y = b * c;
		cout << "Y = " << y;
		break;
	case 7:
		y = a * a + c;
		cout << "Y = " << y;
		break;
	case 3:
		y = a - b * c;
		cout << "Y = " << y;
		break;
	default:
		y = 0;
		cout << "Y = " << y;
		break;
	}

	return 0;
}