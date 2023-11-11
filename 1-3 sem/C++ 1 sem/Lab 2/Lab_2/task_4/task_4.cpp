#include <iostream>
#include <cmath>

using namespace std;

int main() {

	double k, x, y, a = 100000;


	cout << "enter coordinate k: ";
	cin >> k;
	cout << "enter coordinate x: ";
	cin >> x;
	cout << "enter coordinate y: ";
	cin >> y;


	if ((x <= k && x >= 0) && (y > k) && k > 0) {						//  k > 0 outside
		a = y - k;
	}
	else if ((x <= k && x >= 0) && (y < 0) && k > 0) {
		a = abs(y);
	}
	else if ((y <= k && y >= 0) && (x > k) && (k > 0)) {
		a = x - k;
	}
	else if ((y <= k && y >= 0) && (x < 0) && (k > 0)) {
		a = abs(x);
	}


	else if (y < k && y > 0 && x < k && x > 0 && k > 0) {				// k > 0 inside
		if (k - y <= y && k - y <= k - x && k - y <= x) {
			a = k - y;
		}
		else if (k - y >= y &&  y <= k - x && y <= x) {
			a = y;
		}
		else if (x <= y && x <= k - x && x <= k - y) {
			a = x;
		}
		else if (k - x <= y && k - x <= x && k - x <= k - y) {
			a = k - x;
		}
	}


	else if (y > k && y < 0 && x > k && x < 0 && k < 0) {			// k < 0 inside
		if (x - k < abs(x) && x - k < abs(y) && x - k <= y - k) {
			a = x - k;
		}
		else if (abs(x) > x - k && abs(x) < abs(y) && abs(x) < y - k) {
			a = abs(x);
		}
		else if (abs(y) < y - k && abs(y) < abs(x) && abs(y) < x - k) {
			a = abs(y);
		}
		else if (y - k < abs(y) && y - k < abs(x) && y - k <= x - k) {
			a = y - k;
		}
	}
	else if ((x >= k && x <= 0) && (y > 0) && (k < 0)) {			// k < 0 outside
		a = y;
	}
	else if ((x >= k && x <= 0) && (y < k) && (k < 0)) {
		a = k - y;
	}
	else if ((y <= 0 && y >= k) && (x > 0) && (k < 0)) {
		a = x;
	}
	else if ((y <= k && y >= 0) && (x < k) && (k < 0)) {
		a = k - x;
	}


	else if (x == y && k > 0 && x > 0 && y > 0) {					// k > 0 right high diagonal
		a = sqrt((x - k) * (x - k) + (y - k) * (y - k));
	}
	else if (abs(y) == x - k && k > 0 && x > 0 && y < 0) {			// k > 0 right down dia
		a = sqrt((k - x) * (k - x) + y * y);
	}
	else if (y - k == abs(x) && k > 0 && y > 0 && x < 0) {			// k > 0 left high dia
		a = sqrt((y - k) * (y - k) + x * x);
	}
	else if (y == x && k > 0 && x < 0 && y < 0) {					// k > 0 left down dia
		a = sqrt(x * x + y * y);
	}


	else if (k < 0 && x > 0 && y > 0 && x == y) {					// k < 0 right high dia
		a = sqrt(x * x + y * y);
	}
	else if (k < 0 && x > 0 && y < 0 && x == k - y) {				// k < 0 right down dia
		a = sqrt(x * x + (k - y) * (k - y));
	}
	else if (k < 0 && x < 0 && y < 0 && x == y) {					// k < 0 left down dia
		a = sqrt((k - x) *(k - x) + (k - y) * (k - y));
	}
	else if (k < 0 && x < 0 && y > 0 && k - x == y) {				// k < 0 left high dia
		a = sqrt((k - x) * (k - x) + y * y);
	}


	else if (k > 0 && y > k && x > k && x != y) {					// diagonal sectors k > 0
		a = sqrt((x - k) * (x - k) + (y - k) * (y - k));
	}
	else if (k > 0 && y < 0 && x > k && x != y) {
		a = sqrt((x - k) * (x - k) + abs(y) * abs(y));
	}
	else if (k > 0 && y > k && x < 0 && x != y) {
		a = sqrt(abs(x) * abs(x) + (y - k) * (y - k));
	}
	else if (k > 0 && y < 0 && x < 0 && x != y) {
		a = sqrt(abs(x) * abs(x) + abs(y) * abs(y));
	}


	else if (k < 0 && x > 0 && y > 0 && x != y) {					// diagonal sectors k < 0
		a = sqrt(x * x + y * y);
	}
	else if (k < 0 && x > 0 && y < k && x != y) {
		a = sqrt(x * x + (k - y) * (k - y));
	}
	else if (k < 0 && x < k && y > 0 && x != y) {
		a = sqrt(y * y + (k - x) * (k - x));
	}
	else if (k < 0 && x < k && y < k && x != y) {
		a = sqrt((k - y) * (k - y) + (k - x) * (k - x));
	}
	else if (k > 0 && x == 0 || x == k && y <= k && y >= 0) {		// on the perimetr of the square k > 0
		a = 0;
	}
	else if (k > 0 && x >= 0 && x <= k && y == k || y == 0) {
		a = 0;
	}
	else if (k < 0 && x >= k && x <= 0 && y == 0 || y == k) {		// on the perietr of the square k < 0
		a = 0;
	}
	else if (k < 0 && x == k || x == 0 && y <= 0 || y == k) {		
	a = 0;
	}
	cout << a;
	return 0;
}