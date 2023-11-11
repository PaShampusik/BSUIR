#include <iostream>
#include <iomanip>

using namespace std;

double getint()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0) {

	}
	if (a < 2 || a - round(a) != 0) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0) {
			x = false;
		}
		if(a < 2 || a - round(a) != 0) {
			x = true;
		}
	}return round(a);
}

double getdouble()
{
	double a;
	bool x = false;
	cin >> a;

	while (cin.fail() || x) {

		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		
	}return a;
}

int main() {

	int n, m;
	cout << "this program will smooth the specified matrix of size N * M." << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl << "enter number M: " << endl;
	m = getint();

	double** Array = new double* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		Array[i] = new double[m + 2];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << "enter element A[" << i << "]" << "[" << j << "]";
			Array[i][j] = getdouble();
		}
	}
	//safe body for the first massive
	for (int i = 0; i <= n + 1; i++) {
		Array[i][0] = 0;
	}
	for (int i = 0; i <= n + 1; i++) {
		Array[i][m + 1] = 0;
	}
	for (int j = 0; j <= m + 1; j++) {
		Array[0][j] = 0;
	}
	for (int j = 0; j <= m + 1; j++) {
		Array[n + 1][j] = 0;
	}

	cout << endl << "this is our start matrix: " << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << setw(8) << Array[i][j];
		}
		cout << endl;

	}

	double** FinalArray = new double* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		FinalArray[i] = new double[m + 2];
	}

	int c = 8;

	cout << endl << "this is processed matrix: " << endl;

	//smoothing of matrix
	for (int i = 1; i <= n; i++) {
		c = 8;
		for (int j = 1; j <= m; j++) {
			if (Array[i - 1][j - 1] == 0) {
				c--;
			}
			if (Array[i - 1][j] == 0) {
				c--;
			}
			if (Array[i - 1][j + 1] == 0) {
				c--;
			}
			if (Array[i][j - 1] == 0) {
				c--;
			}
			if (Array[i][j + 1] == 0) {
				c--;
			}
			if (Array[i + 1][j - 1] == 0) {
				c--;
			}
			if (Array[i + 1][j] == 0) {
				c--;
			}
			if (Array[i + 1][j + 1] == 0) {
				c--;
			}
			FinalArray[i][j] = (Array[i - 1][j - 1] + Array[i - 1][j] + Array[i - 1][j + 1] + Array[i][j - 1] + Array[i][j + 1] + Array[i + 1][j - 1] + Array[i + 1][j] + Array[i + 1][j + 1]) / c;
			cout << setw(8) << FinalArray[i][j];
			c = 8;
		}
		cout << endl;
	}

	for (int i = 0; i < n + 2; i++)
	{
		delete[] Array[i];
	}
	delete[] Array;

	for (int i = 0; i < n + 2; i++)
	{
		delete[] FinalArray[i];
	}
	delete[] FinalArray;

	return 0;
}

