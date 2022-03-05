#include <iostream>

using namespace std;

int main() {
	int x, a, b, c;
	cin >> x;
	a = x * x;
	b = 69 * a + 8;
	c = x * ((23 * a) + 32);
	cout << " 23x^3 + 69x^2 + 32x + 8 = " << b + c << endl;
	cout << "-23x^3 + 69x^2 - 32x + 8 = " << b - c;
	return 0;
}