#include <iostream>
#include <cmath>

using namespace std;

int main() {

	double x, y, z;

	cout << "enter side x: " << endl;
	cin >> x;
	cout << "enter side y: " << endl;
	cin >> y;
	cout << "enter side z: " << endl;
	cin >> z;

	if (x < y + z && y < x + z && z < x + y) {
		cout << "such triangle can exist";
	}else {
		cout << "such triangle cant exist";
	}

	return 0;
}