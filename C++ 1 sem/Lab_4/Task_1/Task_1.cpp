#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

double getint()
{
	double a;
	bool x = false;
	cout << "enter  number a: ";
	cin >> a;
	if (a - round(a) == 0 && a <= 10000) {

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
		if (a - round(a) == 0 && a <= 10000) {
			x = false;
		}
		else {
			x = true;
		}
	}return a;
}

int main() {
	srand(time(0));
	cout << "this program will get a random integer static massive value of 30 and remove all repeatable elements by swap to 0" << endl;
	cout << "this is start massive:" << endl;
	const int k = 30;
	int A[k];

	for (int i = 0; i < k; i++) {
		A[i] = rand() % 100 + 1;
		cout << A[i] << " ";
	}
	cout << endl << endl << endl << endl << endl;
	cout << "this is new processed masive: " << endl;
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			if (A[i] == A[j]) {
				A[j] = 0;
			}
		}
		cout << A[i] << " ";
	}
	cout << endl;

	return 0;
}