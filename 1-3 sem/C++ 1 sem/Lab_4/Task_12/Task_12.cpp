#include <iostream>
#include <iomanip>

using namespace std;

int ArrayofUnique(int* Array, int length)////////////////////function we needed to get(deleting equal members of massive)
{
	int j, p, n;
	for (j = 0; j < length - 1; j++)
		for (p = j + 1; p < length; p++)
			if (Array[j] == Array[p])
			{
				for (n = p; n < length; n++)
					Array[n] = Array[n + 1];
					length--;
			}
	int* UniqueArr = new int[length];
	cout << endl << "size of new array is " << length << endl << endl << "this is new array: ";
	for (j = 0; j < length; j++)
	{
		UniqueArr[j] = Array[j];
		cout << setw(4) << UniqueArr[j];
	}
	cout << endl;
	delete[] Array;
	return *UniqueArr;
}


int getint()
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


int main()
{
	
	int length;

	///////////genering an array of integers and use our function

	cout << "length of array: ";
	length = getint();

	int* Array = new int[length];

	for (int i = 0; i < length; i++)
	{
		cout << "enter element A[" << i << "]:";
		Array[i] = getint();
	}
	cout << endl << "this is start array: ";
	for (int i = 0; i < length; i++)
	{
		cout << setw(4) << Array[i];
	}
	cout << endl;

	ArrayofUnique(Array, length);
	return 0;
}