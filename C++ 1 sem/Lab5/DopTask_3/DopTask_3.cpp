#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int GetInt()
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
	}return a;
}

void GetAverageArithmetic(vector<int> arr) 
{
	double sum = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i];
	}
	if (sum == 0)
	{
		cout << "Program didnt find needed elements :(";
	}
	else
	{
		double Average = sum / arr.size();
		cout << endl << "Average arithmetic of needed element is: " << Average;
	}
}



int main()
{

	cout << "A two-dimensional dynamic array of integers is specified. The values ​​of the elements of this enter the array from the keyboard.The program will create a dynamic array of elements,located in even columns of this arrayand having an odd valueand will calculate the arithmetic mean of the elements of the dynamic array." << endl;
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
			array[i][j] = GetInt();
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

	cout << endl;

	vector<int> finalarray;

	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < m; j += 2)
		{
			if (array[i][j] / 2 == 1)
			{
				finalarray.push_back(array[i][j]);
			}
		}
	}

	GetAverageArithmetic(finalarray);
	return 0;
}