#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double h, g = 9.81, t;
	cout << "enter h" << endl;
	cin >> h;
	while (h < 0) {
		cout << "enter h" << endl;
		cin >> h;
	}
	t = sqrt((2 * h) / g);			//formula of free falling time
	cout << t;
	return 0;
}

