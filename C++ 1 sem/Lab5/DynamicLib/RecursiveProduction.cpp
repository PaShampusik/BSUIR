#include<iostream>
#include<vector>

using namespace std;

extern "C" __declspec(dllexport)  unsigned long long Prod(const std::vector<double>&v, const int& position_of_num, const int& size) {

	if (size == 1) {
		cout << v[position_of_num - 1] << " " << (position_of_num) << '\n';
		return v[position_of_num - 1] / (position_of_num);
	}
	if (size % 2) {
		return Prod(v, position_of_num / 2, size / 2) * Prod(v, position_of_num / 2 + (size / 2), size / 2) * v[size - 1] / size;
	}
	else {
		return Prod(v, position_of_num / 2, size / 2) * Prod(v, position_of_num / 2 + (size / 2), size / 2);
	}
}
extern "C" __declspec(dllexport) long long RecursiveProduction2(double *arr)
{

}
extern "C" __declspec(dllexport) int GetInt()
{
	double a;
	cin >> a;
	bool x = false;
	if (a - round(a) == 0)
	{

	}
	if (a - round(a) != 0)
	{
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0)
		{
			x = false;
		}
		if (a - round(a) != 0)
		{
			x = true;
		}
	}return a;
}
extern "C" __declspec(dllexport) double GetDouble()
{
	double a;
	cin >> a;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		
	}return a;
}
