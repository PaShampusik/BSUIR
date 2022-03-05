#include<iostream>

using namespace std;

int main() {

	cout << "The program will count the number of interesting numbers up to n by the set t.";

	cout << "enter number of sets t: ";
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
		else { 
			break;
		}
	}

	int n, answer;

	for (int i = 0; i < num; i++)
	{
		cout << "enter number n: ";
		while (true)
		{
			cin >> n;

			if (cin.fail() || n <= 0)
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << endl << "Incorrect input. Try again." << endl;
				continue;
			}
			else {
				break;
			}
		}
		answer = (n + 1) / 10;
		cout << answer << endl;
	}

	return 0;
}