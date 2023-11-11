#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int main() {

	cout << "The program will convert numbers from the reverse code to their natural form" << endl;
	cout << "enter the number: ";

	string s;

	bool x = true;

	while (x)
	{
		getline(cin, s);
		x = false;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != 48 && s[i] != 49)
			{
				cout << "inavalid input, try again:";
				s.clear();
				x = true;
			}
		}
	}

	long long int dec = 0;
	int count = 0;

	for (int i = s.length() - 1; i > 0; i--)
	{
		if (s[0] == 49)
		{
			if (s[i] == 48)
			{
				s[i] = 49;
			}
			else 
			{
				s[i] = 48;
			}
			dec += pow(2, count) * (s[i] - '0');
			count++;
		}
		else {
			dec += pow(2, count) * (s[i] - '0');
			count++;
		}
	}

	if (s[0] == 49)
	{
		cout << endl << dec * (-1) << endl;
	}
	else 
	{
		cout << endl << dec << endl;
	}

	return 0;
}