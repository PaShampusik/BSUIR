#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

double getint()
{
	double a;
	bool x = false;
	cout << "enter  number a: ";
	cin >> a;
	if (a - round(a) == 0) {

	}
	else {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(40000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0) {
			x = false;
		}
		else {
			x = true;
		}
	}return a;
}

int main() {
	srand(time(0));
	int x, i;
	cout << "this program  calculate the sum of all even and the product of all odd members of the array" << endl << endl;

	const int n = 6;
	const int m = 5;

	int A[n][m];

	//filling massive with random numbers less than 10

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			A[i][j] = rand() % 10 + 1;
			cout << setw(2) << A[i][j] << " ";
		}
		cout << endl;
	}

	//calculating sums

	unsigned long long sum1 = 0, sum2 = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] % 2 == 1) {
				sum2 *= A[i][j];
			}
			else {
				sum1 += A[i][j];
			}
		}
	}

	cout << endl << "sum of all even numbers in massive is: " << sum1 << endl;
	cout << "product of all odd members of the array: " << sum2 << endl;
	return 0;
}