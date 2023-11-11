#include<iostream>

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
//rec function//////////////////
unsigned long long PowMod(unsigned long long x, unsigned long long y, unsigned long long n)
{
    if (!y) return 1;

    if (y & 1) return (x * PowMod((x * x) % n, y / 2, n)) % n;

    return PowMod((x * x) % n, y / 2, n);

    int cs = 1;
}
///////////////////////////////
int main() 
{
	unsigned long long	k = -1, n = -1, t = -1, res;

	cout << "Look at the description of the task in Lab file, because it's mad :D" << endl;

    int cs = 1;
	while(k + n + t)
    {
		cout << "enter numbers k, n, t: ";
		k = GetInt();
		n = GetInt();
		t = GetInt();
        int m = 1; for (int i = 0; i < t; i++) m *= 10;

        res = PowMod(k % m, n, m);

		cout << "Case " << cs++ << " result is: " << res << endl;

    }
}