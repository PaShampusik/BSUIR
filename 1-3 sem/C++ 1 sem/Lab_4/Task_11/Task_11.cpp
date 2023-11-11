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
	}return round(a);
}

int main() {

	int n;
	cout << "This program will find the largest diagonal in an integer three-dimensional array with N ^ 3 elements" << endl;
	cout << "enter number N: ";
	n = getint();
	cout << endl;


	int*** Array = new int** [n];
	for (int i = 0; i < n; i++) 
	{
		Array[i] = new int* [n];
		for (int j = 0; j < n; j++)
		{
			Array[i][j] = new int[n];
			for (int  k = 0; k < n; k++)
			{
				cout << "enter element A[" << i << "][" << j << "][" << k << "]: ";
				Array[i][j][k] = getint();
				cout << endl;
			}
		}
	}


	int Compare[4];  ////array for diagonals(4)

	/////////////////diagonal 1
	int sum1 = 0, j = 0, k = 0;
	for (int i = 0; i < n; i++)
	{
		sum1 += Array[i][j][k];
		j++;
		k++;

	}			
	Compare[0] = sum1;

	////////////////diagonal 2
	int sum2 = 0; j = 0, k = n - 1;
	for (int i = 0; i < n; i++)
	{
		sum2 += Array[i][j][k];
		j++;
		k--;
	}
	Compare[1] = sum2;

	////////////////diagonal 3
	int sum3 = 0; j = n - 1, k = n - 1;
	for (int i = 0; i < n; i++)
	{
		sum3 += Array[i][j][k];
		j--;
		k--;
	}
	Compare[2] = sum3;

	////////////////diagonal 4
	int sum4 = 0; j = n - 1, k = 0;
	for (int i = 0; i < n; i++)
	{
		sum4 += Array[i][j][k];
		j--;
		k++;
	}
	Compare[3] = sum4;


	///////////////////comparing diagonals

	int max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (Compare[i] > max)
		{
			max = Compare[i];
		}
	}

	
	////////////writing the biggest diagonal				//		///					//////
	
	cout << "this is the biggest diagonal of the cube matrix: " << endl;
	if (max == Compare[0])																	//
	{	

		j = 0, k = 0;
		for (int i = 0; i < n; i++)															//
		{
			cout << setw(4) << Array[i][j][k];
			j++;
			k++;
		}
	}

	if (max == Compare[1])																	//
	{
		j = 0, k = n - 1;
		for (int i = 0; i < n; i++)
		{
			cout << setw(4) << Array[i][j][k];												//
			j++;
			k--;
		}
	}

	if (max == Compare[2])																	///
	{
		j = n - 1;
		k = n - 1;
		for (int i = 0; i < n; i++)
		{
			cout << setw(4) << Array[i][j][k];												///
			j--;
			k--;
		}
	}

	if (max == Compare[3])																	///
	{
		j = n - 1;
		k = 0;
		for (int i = 0; i < n; i++)
		{
			cout << setw(4) << Array[i][j][k];
			j--;
			k++;
		}
	}

	////////////////////////			//						////					/////////

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			delete[] Array[i][j];
		}
		delete[] Array[i];
	}
	delete[] Array;
	

	return 0;
}