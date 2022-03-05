#include <iostream>
#include <locale.h>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	double a;
	cout << "enter number of mushrooms a: ";
	cin >> a;
	while (a <= 0) {
		cout << endl << "enter number of mushrooms a: ";
		cin >> a;
	}
	if (round(a) == a) {
		if (int(a) % 10 == 1 && int(a) % 100 != 11) {
			cout << "Мы нашли " << a << " гриб";
		}
		else if (int(a) % 100 > 4 && int(a) % 100 < 21) {
			cout << "Мы нашли " << a << " грибов";
		}
		else if (int(a) % 10 >= 2 && int(a) % 10 <= 4 && int(a) % 100 != 12 && int(a) % 100 != 13 && int(a) % 100 != 14) {
			cout << "Мы нашли " << a << " гриба";
		}
		else if ((int(a) % 10 >= 5 && int(a) % 10 <= 9) || (int(a) % 10 == 0)) {
			cout << "Мы нашли " << a << " грибов";
		}
	}
	else {
		cout << "Мы нашли " << a << " гриба";
	}
	return 0;
}