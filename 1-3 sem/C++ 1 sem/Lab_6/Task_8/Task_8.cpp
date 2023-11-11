#include<iostream>
#include<string>

using namespace std;

int main() {

	cout << "Enter 2 srings s and t. Program will say you,can you do such operations with string s to get string t. Look for operations in the task";
	cout << endl;

	int numofsol, k = 1, l, i = 0;

	string origS, newS, anotherS, reversedS;

	while (true)
	{
		cout << "Enter the number of solutions: ";
		cin >> numofsol;
		if (cin.fail() || numofsol < 0)
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

	while (k <= numofsol)
	{
		cout << "Enter your string: ";

		getline(cin, origS);
		cout << "Enter new string: ";

		getline(cin, newS);

		l = origS.size();

		int Length1 = l, Length2 = l, k = 1;

		for (int i = 0, j = l - 2; i < l - 1; i++, j--)
		{
			reversedS.push_back(origS[j]);
		}

		string reversedScopy = reversedS, origScopy = origS;
		anotherS = origS + reversedS;

		if (anotherS == newS)
		{
			cout << endl << "YES" << endl;
			k++;
			origS.clear();
			reversedS.clear();
			newS.clear();
			origScopy.clear();
			reversedScopy.clear();
			anotherS.clear();
			continue;
		}

		for (int i = 0; i < l; i++)
		{
			reversedS = reversedScopy;
			Length2 = l;

			for (; !origS.empty();)
			{
				anotherS = origS + reversedS;
				for (int k = 0; k != origS.size(); k++)
				{
					anotherS.erase(anotherS.size() - 1);
					if (anotherS == newS)
					{
						cout << endl << "YES" << endl;
						break;
					}

				}
				if (anotherS == newS)
				{
					break;
				}
				origS.erase(origS.size() - 1);
				reversedS.erase(0, 1);
			}
			if (anotherS == newS) 
			{ 
				break;
			}
			origS = origScopy.erase(0, 1);
			if (origS.size() == 1) 
			{ 
				continue;
			}
			else
			{
				origS.erase(0, 1);
			}
		}
		if (anotherS != newS) 
		{
			cout << endl << "NO" << endl;
		}
		origS.clear();
		reversedS.clear();
		newS.clear();
		origScopy.clear();
		reversedScopy.clear();
		anotherS.clear();
		k++;
	}
}