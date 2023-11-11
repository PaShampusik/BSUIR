#include <string>
#include <iostream>

using namespace std;


int main() {

	cout << "This program will print without repeating the words of the text in which the first andthe last letters match." << endl;

	char str[255] = "";
	char* dopstr = new char[255];
	int* count = new int[255];
	
	cin.getline(str, 255);
	int k = 0;

	
	for (int i = 0; i < 255; i++)
	{
		if (i == 0)
		{
			count[0] = 0;
			k++;
		}
		if (str[i] == ' ')
		{
			count[k] = i;
			k++;
		}if (str[i] == '\0')
		{
			count[k] = i;
			k++;
		}
	}
	
	for (int i = k - 1; i > 0; i--)
	{
		if (i == 1 && str[0] == str[count[i] - 1])
		{
			for (int j = count[i - 1]; j <= count[i] - 1; j++)
			{
				cout << str[j];
			}
			cout << endl << endl;
		}
		if (str[count[i - 1] + 1]  == str[count[i] - 1])
		{
			for (int j = count[i - 1] + 1; j <= count[i] - 1; j++)
			{
				cout << str[j];
			}
			cout << endl << endl;
		}
	}
	delete[] dopstr;
	delete[] count;
	return 0;
}