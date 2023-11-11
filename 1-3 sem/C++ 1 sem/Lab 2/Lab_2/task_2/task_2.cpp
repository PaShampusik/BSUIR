#include <iostream>

using namespace std;

int main() {
	int X, Y;

	cout << "enter number X: ";
	cin >> X;
	cout << endl << "enter number Y: ";
	cin >> Y;

	if (X - Y > 0) {
		Y = 0;
	}
	else if (Y - X > 0) {
		X = 0;
	}
	else {
		X = 0;
		Y = 0;
	}
	cout << "X = " << X << "  " << "Y = " << Y << endl;

	double A, B, C, K;

	cout << "enter number A: ";
	cin >> A;
	cout << endl << "enter number B: ";
	cin >> B;
	cout << "enter number C: ";
	cin >> C;
	cout << endl << "enter number K: ";
	cin >> K;

	if (A > B && A > C) {
		A = A - K;
	}
	else if (B > C && B > A) {
		B = B - K;
	}
	else if (C > B && C > A) {
		C = C - K;
	}
	else if (A == B && B == C) {
		A = A - K;
		C = C - K;
		B = B - K;
	}
	else if (A == B && B != C) {
		A = A - K;
		B = B - K;
	}
	else if (C == B && C != A) {
		C = C - K;
		B = B - K;
	}
	else if (A == C && C != B) {
		A = A - K;
		C = C - K;
	}	
	cout << "A = " << A << " " << "B = " << B << " " << "C = " << C;

	return 0;
}