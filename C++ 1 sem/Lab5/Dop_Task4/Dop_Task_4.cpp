#include <iostream>
#include <iomanip>

using namespace std;

int GetInt()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0 && a > 0) {
	}
	if (a - round(a) != 0) {
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
		if (a - round(a) != 0) {
			x = true;
		}
	}return a;
}




int MainTask() {
	cout << endl;
	int p, q;
	cout << "there is a recursive function shown in the task, this program will show the result of the sum of all its members" << endl;
	cout << "Enter number p: ";
	p = GetInt();

	///if all nums are negative, then we end the programm

	cout << "enter number q: ";
	cin >> q;
	if (q < 0 && p < 0)
		{
			return 0;
		}

	//////////////////////////////////////////////////////

	while (q <= p || (q > 0 && p < 0))
	{
		cout << "Invalid input, try again, enter p: ";
		cin >> p;
		cout << endl << "enter q: ";
		cin >> q;
		cout << endl;
		if (q / 1 < 0 && p / 1 < 0)
		{
			return 0;
		}
	}
	

	int* F = new int[q + 1];
	long long sum = 0;

	for (int i = p; i < q + 1; i++)
	{
		if (i % 10 > 0) {
			F[i] = i % 10;
		}
		else if (i == 0) {
			F[i] = 0;
		}
		else {
			F[i] = i / 10;
		}
		sum += F[i];
	}
	

	cout << "final sum is: " << sum << endl;
	return MainTask();
}


int main()
{
	MainTask();
	return 0;
}

