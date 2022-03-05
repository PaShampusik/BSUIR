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
	cout << "elemnet A[i][j] will become the bigest among elemnets with k <= i and l <= j matrix of size N * M." << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl << "enter number M: " << endl;
	m = getint();

	double** Array = new double* [n];
	for (int i = 0; i < n; i++) {
		Array[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << "enter element A[" << i + 1 << "]" << "[" << j + 1<< "]";
			Array[i][j] = getdouble();
		}
	}
	cout << endl << "this is our start matrix: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(8) << Array[i][j];
		}
		cout << endl;
	}

	double** FinalArray = new double* [n];
	for (int i = 0; i < n; i++) {
		FinalArray[i] = new double[m];
	}

	/////////////pocessing start matrix into new one

	int k = 0, l = 0;
	double max = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{	
			if (i == 0 && j == 0) {
				FinalArray[0][0] = 0;
			}
			for (int k = 0; k <= i; k++)
			{
				for (int l = 0; l <= j; l++)
				{	
					if (Array[k][l] > max) {
						max = Array[k][l];
					}
				}
			}
			FinalArray[i][j] = max;
			max = 0;
			k = 0;
			l = 0;
			
			
		}
		cout << endl;
	}

	

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(8) << FinalArray[i][j];
		}
		cout << endl;
	}


		for (int i = 0; i < n; i++)
		{
			delete[] Array[i];
		}
		delete[] Array;

		for (int i = 0; i < n; i++)
		{
			delete[] FinalArray[i];
		}
		delete[] FinalArray;
		return 0;
	}
