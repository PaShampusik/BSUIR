#include<iostream>
#include<string>


using namespace std;


int main() {

	string s1, s2;

	long long l, m, num_of_str;
	int num_of_sol, k = 1, count = 1;

	cout << "Program will count the number of strings with entered prefixx and suffixx by module of number M: " << endl;

	while (true)
	{
		cout << "Enter the number of actions: ";
		cin >> num_of_sol;
		if (cin.fail() || num_of_sol < 0)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nIncorrect input. Try again.\n";
			continue;
		}
		else 
		{ 
			break; 
		}
	}
	while (k <= num_of_sol)
	{
		while (true)
		{
			cout << endl << "Enter the length of string S and module number M: ";

			cin >> l >> m;

			if (cin.fail() || l < 0 || m < 0)
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "\nIncorrect input. Try again.\n";
				continue;
			}

			else
			{
				cin.ignore();
				break;
			}
		}

		cout << "Enter String1: ";

		getline(cin, s1);

		cout << "Enter String2: ";

		getline(cin, s2);

		if (s1.size() + s2.size() < l)
		{
			num_of_str = pow(26, l - s1.size() - s2.size()) * 2;
			cout << num_of_str % m << endl;
		}
		else if (s1.size() + s2.size() > l)
		{
			for (int i = 0; i < s1.size(); i++)
			{
				for (int j = 0; j < s2.size(); j++)
				{
					if (s1[i] == s2[j] && s1[i + 1] != s2[j + 1]) 
					{

					}
					else if(s1[i] == s2[j]) 
					{
						count++;
					}
				}
			}

			if (count == 1)
			{
				cout << 0 << endl;
				k++;
			}

			int Empty = l - s1.size() - s2.size() + count;

			if (Empty > 0)
			{
				num_of_str = pow(26, Empty) * 2;
				cout << num_of_str % m << endl;
			}
			else if (Empty == 0) 
			{
				cout << 1 << endl;
			}
			else 
			{
				cout << 0 << endl;
			}
		}
		else if (s1.size() + s2.size() == l)
		{
			cout << 2 << endl;
		}
		s1.clear();
		s2.clear();
		k++;
	}

	return 0;
}