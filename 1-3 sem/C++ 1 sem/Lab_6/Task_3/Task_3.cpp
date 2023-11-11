#include <string>
#include <iostream>

using namespace std;

int main() {

	cout << "This program will enter two lines. The function will determine if they areanagrams(i.e.one line is obtained from another by permutationletters).For example : lines B U K and K U B are anagrams" << endl;

	char str1[80] = "", str2[80] = "";

	cout << "enter first line: ";
	cin >> str1;
	cout << endl << "enter second line: ";
	cin >> str2;
	cout << endl;

	int length1 = 0, length2 = 0;
	
	for (int i = 0; i < 80; i++)
	{
		if (str1[i] == '\0')
		{
			length1 = i;
		}
		if (str2[i] == '\0')
		{
			length2 = i;
		}
	}

	int k = -1;
	if (length1 == length2)
	{
		for (int i = 0; i < length1; i++)
		{
			k = -1;
			for (int j = 0; j < length2; j++)
			{
				if (str1[i] == str2[j])
				{
					k = j;
				}
			}
			if (k >= 0)
			{

			}
			else {
				cout << endl << "this strings are not anagramms";
				break;
			}
		}
	}
	else
	{
		cout << endl << "this strings are not anagramms." << endl;
	}
	

	return 0;
}