#include <string>
#include <iostream>

using namespace std;

int main() {
	char str1[255] = "";
	char* dopstr = new char[255];
	int* count = new int[255];
	char str2[255] = "";
	char str3[255] = "";

	cin.getline(str1, 255);
	int k = 0;

	for (int i = 1; i < 255; i++)
	{
		dopstr = str1;
	}

	for (int i = 1; i < 255; i++)
	{
		if (i == 1)
		{
			count[0] = i;
			k++;
		}
		if (str1[i] == ' ')
		{
			count[k] = i;
			k++;
		}if (str1[i] == '\0')
		{
			count[i] = i;
			k++;
		}
	}
	int n = 0;

	for (int i = k - 1; i >= 0; i--)
	{
		if (str1[count[i - 1] + 1] == str1[count[i] - 1])
		{

			for (int j = str1[count[i - 1] + 1]; j < str1[count[i] - 1]; j++)
			{
				if ()
				{

				}
				str3[n] = str1[j];
			}
			str2.find(str3);
		}
	}
	return 0;
}