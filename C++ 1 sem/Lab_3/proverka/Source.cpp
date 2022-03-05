#include <iostream>
#include <cmath>


using namespace std;
double getint()
{
	double a;
	bool x = false;
	cout << "enter a number: ";
	cin >> a;
	if (a - round(a) == 0){

	}
	else {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(40000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl; 
		if (a - round(a) == 0) {
			x = false;
		}
		else {
			x = true;
		}
	}return a;
}
int main() {
	int a = getint();
	cout << a;



	return 0;
}#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>

using namespace std;

double getint()
{
	double a;
	bool x = false;
	cout << "enter  number a: ";
	cin >> a;
	if (a - round(a) == 0) {

	}
	else {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(40000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0) {
			x = false;
		}
		else {
			x = true;
		}
	}return a;
}

int main() {

	setlocale(LC_ALL, "Russian");
	int a = getint();
	cout << a;
	return 0;
}