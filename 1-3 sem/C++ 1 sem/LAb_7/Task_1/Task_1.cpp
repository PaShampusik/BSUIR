#include<iostream>
#include<string>
#include<cmath>

using namespace std;


int main() {

	cout << "Translates numbers from one number system to another(from ternary to seventeen)." << endl;
	cout << "enter the number: ";

	string s;

	bool x = true;

	while (x)
	{
		getline(cin, s);
		x = false;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != 48 && s[i] != 49 && s[i] != 50)
			{
				cout << "inavalid input, try again:";
				s.clear();
				x = true;
			}
		}
	}

	long long int dec = 0;
	int count = 0;

	for (int i = s.length() - 1; i >= 0; i--)
	{
		dec += pow(3, count) * (s[i] - '0');
		count++;
	}

	string seven = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	string answer;
	int k = 0;

	while (dec > 0)
	{
		answer.push_back(seven[dec % 17]);
		dec /= 17;
		k++;
		if (dec == 0)
		{
			answer[k] = dec;
		}

	}

	cout << endl;

	for (int i = answer.size() - 1; i >= 0; i--)
	{
		cout << answer[i];
	}
	
	cout << endl;

	return 0;
}