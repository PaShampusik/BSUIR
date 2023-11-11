#include <iostream>
#include <iomanip>

using namespace std;

unsigned long long int GetInt()
{
	unsigned long long int a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0 && a > 0) {
	}
	if (a - round(a) != 0 || a < 0) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0 && a > 0) {
			x = false;
		}
		if (a - round(a) != 0 || a < 0) {
			x = true;
		}
	}return a;
}
//recfunction///////////////////////////////
unsigned long long int SumGOD(long long n)
{
	unsigned long long int k = (n + 1) / 2;
	
	if (n == 0) {
		return 0;
	}

	return k * k + SumGOD(n / 2);
}
//////////////////////////////////////////////




int main() {
	cout << "Let f (n) be the greatest odd divisor of a natural number n. According to the given natural n the program will calculate the value of the sum f(1) + f(2) + ... + f(n)." << endl;

	unsigned long int sum = 0;
	unsigned long long int n;
	cout << "Enter number p: ";
	n = GetInt();
	cout << endl;
	cout << "total sum of highest odd dividers to p number is: " << SumGOD(n) << endl;
	return 0;
}






