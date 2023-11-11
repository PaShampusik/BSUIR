#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double x, n, m, K, A, D, Y;
	cout << "enter number n: ";
	cin >> n;
	cout << endl << "enter number m: ";
	cin >> m;
	cout << endl << "enter number x: ";
	cin >> x;
	cout << endl << "enter number K: ";
	cin >> K;
	A = fabs(n + m);
	D = tan(x);
	if (A != 0) {					//if we dont divide by zero
		Y = 1.29 + K / A + D * D;
		cout << endl << "Y = ";
		cout << Y;
	}
	else {							//if we divide by zero
		cout << "cant be diveded by zero";
	}
	return 0;
}