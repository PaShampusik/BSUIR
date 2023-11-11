#include <iostream>
#include <iomanip>

using namespace std;

double GetDouble()
{
	double a;
	cin >> a;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
	}return a;
}

int GetInt()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0 && a >= 1) {

	}
	if (a - round(a) != 0 || a < 1) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0 && a >= 1) {
			x = false;
		}
		if (a - round(a) != 0 || a < 1) {
			x = true;
		}
	}return a;
}

//function/////////////////

void MainTask(double** array, int n, int m) {


	cout << "This is reversed massive: " << endl;

	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = m - 1; i >= 0; i--)
		{			
			cout << setw(5) << array[j][i];	
		}
		cout << endl;
	}

	int count = 0;
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (array[i][j] == 0)
			{
				count++;
				cout << count << " element that is equal to 0 has indexes " << i + 1 << " and " << j + 1 << " and has value of " << array[i][j];
				cout << endl;
			}			
		}
	}

	if (count == 0) 
	{
		cout << endl << "program didnt find any elements equal to 0.";
	}
}

////////////////////////////////////////////

int main()
{
	cout << "The program will create a two-dimensional dynamic array of real numbers. Will determine whether there are elements with zero value among them.If there are such elements, it will determine their indicesand the total number.Will rearrange the elements of this the array in reverse orderand will print to the screen." << endl;
	cout << "Enter Number N: ";
	int n = GetInt();
	cout << endl << "Enter Number M: ";
	int m = GetInt();
	cout << endl;

	double** array = new double* [n];
	for (int i = 0; i < n; i++)
	{
		array[i] = new double[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "Enter element [" << i + 1 << "][" << j + 1 << "]" << " of your massive: ";
			array[i][j] = GetDouble();
			cout << endl;
		}

	}


	cout << "this is our start massive: " << endl;

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			cout << setw(5) << array[j][i];
		}
		cout << endl;
	}
//doing neccessary things with massive by one function
	MainTask(array, n, m);
	return 0;
}