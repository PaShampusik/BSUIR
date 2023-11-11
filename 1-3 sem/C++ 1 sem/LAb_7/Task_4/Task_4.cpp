#include<iostream>
#include<string>

using namespace std;

string GetSubstraction(string seventinth1, string seventinth2, string example1);
string GetSum(string seventinth1, string seventinth2, string example1);

string GetSum(string seventinth1, string seventinth2, string example1)
{	
	string air;
	string answer;

	int x = 0, y = 0, z = 0, count = 0, l = 0;

	if (seventinth1[0] == '-' && seventinth2[0] == '-')
	{
		l = 1;
		seventinth1.erase(0, 1);
		seventinth2.erase(0, 1);
	}
	if (seventinth1[0] == '-' && seventinth2[0] != '-')
	{
		return GetSubstraction(seventinth1, seventinth2, example1);
	}
	if (seventinth1[0] == '-' && seventinth2[0] == '-')
	{
		return GetSubstraction(seventinth1, seventinth2, example1);
	}



	if (seventinth1.length() > seventinth2.length())
	{
		seventinth2.insert(0, seventinth1.length() - seventinth2.length(), '0');
	}
	if (seventinth1.length() < seventinth2.length())
	{
		air = seventinth1;
		seventinth1 = seventinth2;
		seventinth2 = air;
		air.clear();
		seventinth2.insert(0, seventinth1.length() - seventinth2.length(), '0');
	}

	for (int i = seventinth1.length() - 1; i >= 0; i--)
	{
		for (int j = 0; j < 17; j++)
		{
			if (seventinth1[i] == example1[j])
			{
				x = j;
			}
			if (seventinth2[i] == example1[j])
			{
				y = j;
			}
		}

		count = x + y + z;

		if (count < 17)
		{
			z = 0;
			air.push_back(example1[count]);
			answer.insert(0, air);
			air.clear();

		}

		if (count > 16)
		{
			z = 1;
			count -= 17;
			air.push_back(example1[count]);
			answer.insert(0, air);
			air.clear();
		}
	}

	if (l == 1)
	{
		answer.insert(0, "-");
	}
	cout << answer << endl;

	return answer;
}

string GetSubstraction(string seventinth1, string seventinth2, string example1)
{
	string air;
	string answer;

	if (seventinth1[0] == '-' && seventinth2[0] != '-')
	{
		return GetSum(seventinth1, seventinth2, example1);
	}
	if (seventinth1[0] != '-' && seventinth2[0] == '-')
	{
		return GetSum(seventinth1, seventinth2, example1);
	}
	if (seventinth1[0] != '-' && seventinth2[0] != '-')
	{
		
	}
	if (seventinth1[0] == '-' && seventinth2[0] == '-')
	{
		air = seventinth1;
		seventinth1 = seventinth2;
		seventinth2 = air;
		air.clear();
		seventinth1.erase(0, 1);
		seventinth2.erase(0, 1);
	}

	int x = 0, y = 0, z = 0, count = 0, l = 0;

	if (seventinth2.length() > seventinth1.length())
	{
		seventinth1.insert(0, seventinth1.length() - seventinth2.length(), '0');
	}
	if (seventinth1.length() > seventinth2.length())
	{
		seventinth2.insert(0, seventinth1.length() - seventinth2.length(), '0');
	}

	for (int i = seventinth1.length() - 1; i >= 0; i--)
	{
		for (int j = 0; j < 17; j++)
		{
			if (seventinth1[i] == example1[j])
			{
				x = j;
			}
			if (seventinth2[i] == example1[j])
			{
				y = j;
			}
		}

		count = x - y;

		if (count < 0 && i != 0)
		{
			count += 17;
			seventinth1[i - 1] -= 1;
			z = 0;
			air.push_back(example1[count]);
			answer.insert(0, air);
			air.clear();
		}
		if (count > 0)
		{
			air.push_back(example1[count]);
			answer.insert(0, air);
			air.clear();
		}
		if (count < 0 && i == 0)
		{

			air.push_back(example1[abs(count)]);
			answer.insert(0, air);
			air.clear();
			answer.insert(0, "-");
		}
	}
	
	cout << answer << endl;

	return answer;
}


string GetString(string s, string valid)
{
	bool x = true;
	while (x)
	{
		getline(cin, s);

		for (int i = 0; i < s.length(); i++)
		{
			x = true;

			for (int j = 0; j < valid.length(); j++)
			{
				if (s[i] == valid[j])
				{
					x = false;
					break;
				}
			}
			if (x == true)
			{
				cout << endl << "this is invalid input, try again: ";
				break;
			}
		}
	}
	return s;
}

int main() {

	cout << "Add and subtract numbers in a given system numerals(base 17).";

	string example1 = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9','a', 'b', 'c', 'd', 'e', 'f', 'g', '-' };
	string seventinth1;
	string seventinth2;

	char a;

	cout << "enter + or -, it depends on your choice: ";
	cin >> a;
	cout << endl;

	while (a != '+' && a != '-')
	{
		cout << "invalid input, try again: ";
		cin >> a;
		cout << endl;
	}

	cout << endl << "enter first number in seventinth system: ";
	seventinth1 = GetString(seventinth1, example1);

	cout << endl << "enter second number in seventinth system: ";
	seventinth2 = GetString(seventinth2, example1);

	if (a == '-')
	{
		GetSubstraction(seventinth1, seventinth2, example1);
	}if (a == '+')
	{
		GetSum(seventinth1, seventinth2, example1);
	}

	return 0;
}








