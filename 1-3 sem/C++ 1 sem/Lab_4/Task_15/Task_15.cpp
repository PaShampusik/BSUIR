#include <iostream>
#include <iomanip>

using namespace std;

int getint()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0) {

	}
	if (a - round(a) != 0 || a > 625) {
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
		if (a - round(a) != 0 || a > 625) {
			x = true;
		}
	}return round(a);
}


int main() {

	int n;
	cout << "This program will calculate in which column and row of the given matrix the element N (N < 626), entered by the user, is located." << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl;


	int** Array = new int* [25];
	for (int i = 0; i < 25; i++) {
		Array[i] = new int[25];
	}

	int a = 1;


	////////////////building matrix

	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			if (i == 0 && j == 0)
			{
				Array[i][j] = a;
				a++;
			}
			if (i == j && (i != 0 && j != 0))
			{
				for (int k = j; k >= 0; k--)
				{
					Array[i][k] = a;
					a++;
				}
			}
			if (i < j)
			{
				Array[i][j] = a;
				a++;
			}

		}
	}

	//////////////////printing matrix
	
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			cout << setw(4) << Array[i][j];
		}
		cout << endl;
	}

	///////////////// finding element

	int b = -1, c = -1;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (Array[i][j] == n) 
			{
				b = i;
				c = j;
			}
		}
	}

	cout << endl << "element that you entered is placed in " << b + 1 << " row and " << c + 1 << " column" << endl;

	for (int i = 0; i < 25; i++)
	{
		delete[] Array[i];
	}
	delete[] Array;
	return 0;
}