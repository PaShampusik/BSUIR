#include<iostream>
#include<string>


using namespace std;

int main() {

	cout << "This program find the longest substring that is not a palindrome.";

	string s1, s2, s3;

	getline(cin, s1);

	int b = 0, count = 0;


	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = i + 1; j < s1.size(); j++)
		{

			s2 = s1.substr(i, j - i + 1);
			b = s2.size() - 1;

			for (int k = 0; k < s2.size() / 2; k++)
			{
				if (s2[k] != s2[b])
				{
					count++;
				}
				b--;
			}

			if (count > 0 && s2.size() > s3.size())
			{
				s3 = s2;
				s2.clear();
			}

			else
			{
				s2.clear();
			}
			count = 0;
		}
	}

	cout << s3;

	return 0;
}