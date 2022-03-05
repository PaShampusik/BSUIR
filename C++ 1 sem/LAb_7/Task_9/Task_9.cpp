#include<iostream>

using namespace std;

int main() {

	cout << "The program will display the number n written in the specified number system." << endl;

	cout << "enter number t: ";
	int num;

	while (true)
	{
		cin >> num;

		if (cin.fail() || num <= 0)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Incorrect input. Try again." << endl;
			continue;
		}
		else 
		{
			break;
		}
	}

	int b = 1, i = 0;

	while (b < num)
	{
		b *= 3;
		i++;
	}

	int c = 0;

	double* arr = new double[i];

	int count = 0;

	for (int j = i - 1; j >= 0; j--)
	{
		c = num / pow(3, j);
		if (c == 0)
		{
			arr[count - 1] -= 1;
			c = 3; 
		}
		
		arr[count] = c;
		c = 0;
		num = num - (num / int(pow(3, j))) * pow(3,j);
		count++;
	}

	int  k = 0;

	if (arr[0] == 0)
	{
		k = 1;
	}
	for (; k < count; k++)
	{
		cout << arr[k];
	}

	delete[] arr;


	return 0;
}