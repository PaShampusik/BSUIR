#include<iostream>
#include<vector>

using namespace std;

int main()
{
	cout << "Program will will find two decimal number in your position." << endl;

	long long pos;

	while (true)
	{
		cout << endl << "Enter your position: ";
		cin >> pos;

		if (cin.fail() || pos <= 0)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nIncorrect input. Try again.\n";
			continue;
		}
		else break;
	}

	vector<long long> twodec;

	char numstr[255] = "";
	for (unsigned long long num = 1; num < pow(10, 14); num++)
	{
		unsigned long long numcpy = num;

		string sec_notation;

		while (numcpy >= 1) //two-based form
		{
			sec_notation.insert(0, 1, numcpy % 2 + '0');
			numcpy /= 2;
		}

		numcpy = num;
		long l = sec_notation.length();
		bool f = false;

		while (numcpy > 0) // compairing
		{
			int mod = numcpy % 10;

			if (sec_notation[l - 1] - '0' == mod) 
			{
				f = true;
				l--;
			}
			else
			{
				f = false;
				break;
			}
			numcpy /= 10;
		}
		if (f)
		{
			twodec.push_back(num); // writing a number into massive
		}

		if (twodec.size() == pos) // is index of massiv equal to needable 
		{
			cout << twodec[pos - 1] << endl;
			return 0;
		}
	}
}