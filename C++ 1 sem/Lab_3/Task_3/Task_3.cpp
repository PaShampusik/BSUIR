#include <iostream>
#include <cmath>


using namespace std;

int main() {
	double pi = 3.1415, b = pi / 2, h, x;
	
	h = pi / 40;
	for (int i = 0; i < 21; i++) {
		x = h * i;
		cout << "function sin(x) - cos(x) in point " << x << " = " << sin(x) - cos(x) << endl;
	}
	return 0;
}