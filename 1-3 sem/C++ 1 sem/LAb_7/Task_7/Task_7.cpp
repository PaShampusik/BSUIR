#include<iostream>

using namespace std;

int Addition(int FirstNumber, int SecondNumber)
{
	int result = FirstNumber ^ SecondNumber, numrank = (FirstNumber & SecondNumber) << 1;

	while (numrank)
	{
		int tmp = result;
		result ^= numrank;
		numrank = (tmp & numrank) << 1;
	}

	return result;
}

int Subtraction(int FirstNumber, int SecondNumber) 
{
	SecondNumber = Addition(~SecondNumber, 1);

	return Addition(FirstNumber, SecondNumber);
}

int Multiplication(int FirstNumber, int SecondNumber)
{
	int result = 0;

	while (SecondNumber)
	{
		if (SecondNumber & 1) result = Addition(result, FirstNumber);
		FirstNumber <<= 1;
		SecondNumber >>= 1;
	}
	return result;
}

int Divide(int FirstNumber, int SecondNumber) 
{
	int result = 0;
	while (FirstNumber >= SecondNumber)
	{
		result = Addition(result, 1);
		FirstNumber = Subtraction(FirstNumber, SecondNumber);
	}
	return result;
}

int Modulo(int FirstNumber, int SecondNumber)
{
	int result = Subtraction(FirstNumber, Multiplication(Divide(FirstNumber, SecondNumber), SecondNumber));

	return result;
}

int main()
{
	cout << "Program will show modulo of your number and 11, 31, 131." << endl;
	int num;

	while (true)
	{
		cout << "\nEnter your number: ";
		cin >> num;

		if (cin.fail() || num <= 0)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << endl << "Incorrect input.Try again." << endl;
			continue;
		}
		else 
		{
			break;
		}
	}

	int myVariant[] = { 11, 31, 113 };

	for (int i = 0; i < 3;)
	{
		if (Modulo(num, myVariant[i]) != 0)
		{
			cout << "The modulo of your number and " << myVariant[i] << " is " << Modulo(num, myVariant[i]) << endl;
		}

		else 
		{ 
			cout << "Your number divide to " << myVariant[i] << " without modulo." << endl; 
		}
		i = Addition(i, 1);
	}

}