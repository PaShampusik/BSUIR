#include <iostream>
#include<math.h>
using namespace std;


int main()
{
	long long square = 0;
	long long a1, b1, c1, d1, a2, b2, c2, d2, max_side;
	cin >> a1 >> b1 >> c1 >> d1;
	cin >> a2 >> b2 >> c2 >> d2;

	
	if (c1 > c2)
	{
		swap(c1, c2);
		swap(a1, a2);
		swap(b1, b2);
		swap(d1, d2);
	}
	
	struct point
	{
		long long x;
		long long y;
	};

	point first = { a1, b1 };
	point second = { a2, b2 };
	point third = { a1 - d1, b1 -d1 };
	point fourth = { a2 - d2, b2 - d2 };

	if (second.x < third.x || first.x < fourth.x || third.y > second.y || first.y < fourth.y)	
	{
		cout << 0;
		return 0;
	}	
	int x = min(first.x, second.x) - max(third.x, fourth.x);
	int y = max(third.y, fourth.y) - min(first.y, second.y);
	square = abs(x) * abs(y);
	
	long long high = 0;
	if (c2 - d2 > c1) {
		cout << 0;
		return 0;
	}
	if (c2 - d2 < c1 && c1 - d1 < c2 - d2) {
		high = abs(c1 - c2 + d2);
		cout << square * high;
		return 0;
	}
	if (c2 - d2 < c1 && c1 - d1 > c2 - d2) {
		high = d1;
		cout << square * high;
		return 0;
	}
	return 0;
}

