#include<iostream>
#include<string>
#include <vector>

using namespace std;

int main() {

	cout << "The program will convert the number from the Arabic numeral system to Roman.";
	cout << "enter number n: ";

	int num;
	cin >> num;

	vector<string> roman_numerals = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "L", "C", "D", "M", "Z"};
	int arabic_numerals[15] = { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 50, 100, 500, 1000, 2000 };

	string answer;
	int count;

	while (num > 0)
	{
		for (int i = 14; i >= 0; i--)
		{
			if (num > 9)
			{
				count = num / arabic_numerals[i];
				for (int j = 0; j < count; j++)
				{
					answer+=roman_numerals[i];
				}
				num -= count * arabic_numerals[i];
				count = 0;
			}
			if (num < 10 && num != 0)
			{
				answer += roman_numerals[num - 1];
				num = 0;
			}
			if (num == 0)
			{
				break;
			}
		}
	}

	cout << answer;
	return 0;
}