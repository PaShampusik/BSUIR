#include<iostream>

using namespace std;

int main() {

	long long num = 0, sum = 0;

	char s[255] = "";

	cout << "Program will count the sum of the numbers in the string." << endl;
	cout << "Enter your string: ";

	cin.getline(s, 255);

	for (int i = 0; s[i] != '\0'; i++)
	{

		int j = i + 1;

		if (s[i] >= 48 && s[i] <= 57)
		{
			if (s[j] >= 48 && s[j] <= 57)
			{

				num = ((long long)s[j - 1] - '0') * 10 + (s[j] - '0');
				j++;
				i++;

				while (s[j] >= 48 && s[j] <= 57)
				{
					num = num * 10 + (s[j] - '0');
					j++;
					i++;
				}

				sum += num;
			}
		}
	}

	cout << endl << "The summ is: " << sum << endl;

	return 0;
}