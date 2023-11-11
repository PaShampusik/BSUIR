#include <iostream>


using namespace std;

int main() {
	double a, b;
	bool c;
	cout << "enter number a: ";
	cin >> a;
	cout << endl << "enter number b: ";
	cin >> b;
	c = a > b;
	c ? cout << "a is bigger then b" : a == b ? cout << "a is equal to b" : cout << "b is bigger then a";
	return 0;
	

	
}