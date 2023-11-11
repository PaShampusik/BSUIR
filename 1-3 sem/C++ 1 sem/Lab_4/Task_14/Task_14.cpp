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
		if (a < 2 || a - round(a) != 0) {
			x = true;
		}
	}return round(a);
}

double getsymbols()
{
	char a;
	bool x = false;
	cin >> a;
	if ((int)a == 42 || (int)a == 46){

	}
	if ((int)a != 42 && (int)a != 46) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if ((int)a == 42 || (int)a == 46) {
			x = false;
		}
		if ((int)a != 42 && (int)a != 46) {
			x = true;
		}
	}return a;
}

int main() {

	int n, m;
	cout << "This program accepts a matrix of dimensions N * M, consisting of points and stars, points are an empty field, asterisks are mines, this program will display a field for the game sapper with open cells" << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl << "enter number M: ";
	m = getint();

	char** Array = new char* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		Array[i] = new char[m + 2];
	}

	for (int i = 0; i < n + 2; i++)
	{
		for (int j = 0; j < m + 2; j++)
		{
			Array[i][j] = 46;
		}
	}

	/////////////filling space with symbols 

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << "enter element A[" << i << "]" << "[" << j << "]";
			Array[i][j] = getsymbols();
		}
	}


	cout << endl << "this is our start matrix: " << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << setw(4) << Array[i][j];
		}
		cout << endl;
	}

	char** FinalArray = new char* [n + 2];
	for (int i = 0; i < n + 2; i++) {
		FinalArray[i] = new char[m + 2];
	}


	int count = 48;
	cout << endl << "this is final matrix: " << endl;


	////////////building final matrix

	for (int i = 1; i <= n ; i++)
	{
		for (int j = 1; j <= m; j++)
		{ 
			if ((int)Array[i][j] == 42) {
				cout << setw(4) << (char)Array[i][j];
				continue;
			}
			if ((int)Array[i][j] != 42)
			{
				if ((int)Array[i - 1][j - 1] == 42)
				{
					count++;
				}
				if ((int)Array[i - 1][j] == 42)
				{
					count++;
				}
				if ((int)Array[i - 1][j + 1] == 42)
				{
					count++;
				}
				if ((int)Array[i][j - 1] == 42)
				{
					count++;
				}
				if ((int)Array[i][j + 1] == 42)
				{
					count++;
				}
				if ((int)Array[i + 1][j - 1] == 42)
				{
					count++;
				}
				if ((int)Array[i + 1][j] == 42)
				{
					count++;
				}
				if ((int)Array[i + 1][j + 1] == 42)
				{
					count++;
				}
				FinalArray[i][j] = (char)count;
				count = 48;
				cout << setw(4) << FinalArray[i][j];
			}
			
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
}