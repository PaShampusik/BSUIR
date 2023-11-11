#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double GetInt()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0) {
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
		if (a - round(a) == 0) {
			x = false;
		}
		if (a - round(a) != 0) {
			x = true;
		}
	}return int(a);
}

double Get5()
{
	double a;
	bool x = false;
	cin >> a;
	if (a == 5) {

	}
	if (a != 5) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a == 5) {
			x = false;
		}
		if (a != 5) {
			x = true;
		}
	}return round(a);
}

double Get6()
{
	double a;
	bool x = false;
	cin >> a;
	if (a == 6) {

	}
	if (a != 6) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a == 6) {
			x = false;
		}
		if (a != 6) {
			x = true;
		}
	}return round(a);
}

void MainTask() {
	cout << "A two-dimensional dynamic array of integers A of dimension n  k is specified.Enter the dimension of the array(n = 5, k = 6) from the keyboard.Array element values enter from the keyboard.The program will create a dynamic array from the elements located onof the main diagonal of the matrix and having an even value.Calculate the product elements of a dynamic array.The created array and the result of the product will be displayed on the screen." << endl;
	cout << "Enter Number N: ";
	int n = Get5();
	cout << endl << "Enter Number M: ";
	int m = Get6();
	cout << endl;

	vector<vector<int>> array(n, vector<int>(m));
	

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			cout << "Enter element [" << j + 1 << "][" << i + 1 << "]" << " of your massive: ";
			array[j][i] = GetInt();
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

	vector<int> finalarray;

	int count = 0;


	/// //////////////////////////////filling final array
	

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			if (array[j][i] % 2 == 0 && i == j)
			{
				finalarray.push_back(array[j][i]);
				
			}
		}
		
	}


	/////////////////////showoffinalarray

	int b = finalarray.size();
	cout << "this is our final array: " << endl;

	for (int i = 0; i < b; i++)
	{
		cout << setw(5) << finalarray[i];
	}
	
}


int main()
{
	MainTask();

	cout << endl;

	return 0;
}