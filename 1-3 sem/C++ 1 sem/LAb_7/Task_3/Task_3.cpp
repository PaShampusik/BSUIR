#include<iostream>
#include<string>
#include<cmath>

using namespace std;

string GetString(string s, int num) {

	string t;
	int a = -1;
	int b = num;
	if (b >= 0)
	{
		t.push_back('0');
		s.insert(0, t, 0, 1);
		t.clear();

		while ( s.length() != 8)
		{
			a = num % 2;
			t.push_back(a + '0');
			s.insert(1, t, 0, 1);
			t.clear();
			num /= 2;
		}
	}
	else 
	{
		t.push_back('1');
		s.insert(0, t, 0, 1);
		t.clear();

		num *= -1;
		while ( s.length() != 8)
		{
			a = abs(num % 2 - 1);
			t.push_back(a + '0');
			s.insert(1, t, 0, 1);
			t.clear();
			num /= 2;
		}
	}
	
	return s;
}

int main() {

	cout << "The program will find the sum of binary numbers given in natural form.The addition will be done in reverse.The answer will express in direct code." << endl;
	cout << "enter number 1: ";
	int num1;
	cin >> num1;

	cout << "enter number 2: ";
	int num2;
	cin >> num2;

	string num_1;
	string num_2;
	string answer;

	num_1 = GetString(num_1, num1);
	num_2 = GetString(num_2, num2);
	
	int x = 0, b = 0;

	for (int i = max(num_1.length(), num_2.length()) - 1; i >= 0; i--)
	{
		if (num_1[i] + num_2[i] + x == 96)
		{
			answer.insert(0, "0");
			x = 0;
		}
		else if(num_1[i] + num_2[i] + x == 97)
		{
			answer.insert(0, "1");
			x = 0;
		}
		else if (num_1[i] + num_2[i] + x == 98 && i != 0)
		{
			answer.insert(0, "0");
			x = 1;
		}
		else if (num_1[i] + num_2[i] + x == 99 && i != 0)
		{
			answer.insert(0, "1");
			x = 1;
		}



		if (num_1[i] + num_2[i] + x == 98 && i == 0)
		{
			answer.insert(0, "0");
			num_1 = answer;
			answer.clear();
			b = max(num_1.length(), num_2.length());
			num_2.clear();
			num_2.append(b - 2, '0');
			num_2.append(1, '1');
			i = max(num_1.length(), num_2.length());
		}
		else if (num_1[i] + num_2[i] + x == 99 && i == 0)
		{
			answer.insert(0, "1");
			num_1 = answer;
			answer.clear();
			b = max(num_1.length(), num_2.length());
			num_2.clear();
			num_2.append(b - 2, '0');
			num_2.append(1, '1');
			i = max(num_1.length(), num_2.length());
		}
	}

	if (answer[0] == 48)
	{
		for (int i = 1; i < answer.length(); i++)
		{
			cout << answer[i];
		}
	}
	if (answer[0] == 49)
	{
		cout << "-";

		for (int i = 1; i < answer.length(); i++)
		{
			if (answer[i] == 48)
			{
				answer.replace(i, 1, 1, '1');
				cout << answer[i];
			}
			else if (answer[i] == 49)
			{
				answer.replace(i, 1, 1, '0');
				cout << answer[i];
			}
		}
	}
	return 0;
}