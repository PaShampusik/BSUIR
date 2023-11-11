#include <iostream>
#include <iomanip>

using namespace std;

int getint()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0 && a > 0) {
		x = false;
	}
	if (a - round(a) != 0 || a <= 0) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0 && a > 0) {
			x = false;
		}
		if (a - round(a) != 0 || a <= 0) {
			x = true;
		}
	}return round(a);
}

int main() {

	cout << "" << endl;
	cout << "enter number N: ";

	int n = getint();

	cout << endl;

	int* Array = new int[n];

	for (int i = 0; i < n; i++)
	{
		cout << "enter the number of sockets in the " << i + 1 << " extension: ";
		Array[i] = getint();
		cout << endl;
	}

	int sum = 0;


	//////////////////sum of all socckets

	for (int i = 0; i < n; i++)
	{
		sum += Array[i];
	}

	//////output an max optimal number of sockets

	cout << endl << "the number of free rezet is equal to: " << sum - (n - 1);
	
	delete[] Array;
}