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
	else {
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
		else {
			x = true;
		}
	}return round(a);
}

int main() {

	int n, m;
	cout << "this program will calculate number of local minimums in matrix N * M" << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl << "enter number M: ";
	m = getint();

	int** Array = new int* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		Array[i] = new int[m + 2];
	}

	///safe body(filling with int max) for not to catch memory error

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << "enter element A[" << i << "]" << "[" << j << "]";
			Array[i][j] = getint();
		}
	}
	for (int i = 0; i <= n + 1; i++) {
		Array[i][0] = INT_MAX;
	}
	for (int i = 0; i <= n + 1; i++) {
		Array[i][m + 1] = INT_MAX;
	}
	for (int j = 0; j <= m + 1; j++) {
		Array[0][j] = INT_MAX;
	}
	for (int j = 0; j <= m + 1; j++) {
		Array[n + 1][j] = INT_MAX;
	}

	cout << endl << "this is our matrix: " << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << setw(5) << Array[i][j];
		}
		cout << endl;
	}

	///calcilating  number of local minimums

	int k = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (Array[i - 1][j - 1] > Array[i][j] && Array[i - 1][j] > Array[i][j] && Array[i - 1][j + 1] > Array[i][j] && Array[i][j - 1] > Array[i][j] && Array[i][j + 1] > Array[i][j] && Array[i + 1][j - 1] > Array[i][j] && Array[i + 1][j] > Array[i][j] && Array[i + 1][j + 1] > Array[i][j]) {
				k++;
			}
		}
	}
	cout << endl <<  "total number of local minimums is: " << k << endl;
	return 0;

}