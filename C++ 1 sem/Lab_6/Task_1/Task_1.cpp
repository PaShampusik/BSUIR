#include <string>
#include <iostream>

using namespace std;

int main() {

	cout << "this program will count the number of brackets of various types in a line." << endl;

	char str[80] = "";

	cin.getline(str, 80);

	int count = 0;
		for (int i = 0; i < 80; i++)
		{
			if (str[i] == 40 || str[i] == 41 || str[i] == 91 || str[i] == 93 || str[i] == 123 || str[i] == 125) 
			{
				count++;
			}
			
		}
		cout << "total number of ... is: " << count;
		return 0;
}