#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double X1, Y1, X2, Y2, X3, Y3, L12, L13, L23, p, S, h1, h2, h3, a3rad, a2rad,
		a1rad, a3, a2, a1, pi = 3.1415, m1, m2, m3, bis1, bis2, bis3, R, r, C, c, Sofsmallcircle, Sofbigcircle, P;
	cout << "enter x1: ";
	cin >> X1;
	cout << "enter y1: ";
	cin >> Y1;
	cout << "enter x2: ";
	cin >> X2;
	cout << "enter y2: ";
	cin >> Y2;
	cout << "enter x3: ";
	cin >> X3;
	cout << "enter y3: ";
	cin >> Y3;

	L12 = sqrt(pow(fabs(X1 - X2), 2) + pow(fabs(Y1 - Y2), 2));				//length of sides of triangle
	L13 = sqrt(pow(fabs(X1 - X3), 2) + pow(fabs(Y1 - Y3), 2));
	L23 = sqrt(pow(fabs(X2 - X3), 2) + pow(fabs(Y2 - Y3), 2));
	cout << "  Length of sides " << endl << "l12 = " << L12 << endl << "l13 = " << L13 << endl << "l23 = " << L23 << endl;

	p = (L12 + L13 + L23) / 2;
	S = sqrt(p * (p - L12) * (p - L13) * (p - L23));		//area, type ¹ 1

	h3 = (2 * S) / L12;				//heghts
	h2 = (2 * S) / L13;
	h1 = (2 * S) / L23;
	cout << "  Heights falling from points 1, 2, 3" << endl << "h1 = " << h1 << endl << "h2 = " << h2 << endl << "h3 = " << h3 << endl;

	m1 = 0.5 * sqrt(2 * pow(L12, 2) + 2 * pow(L13, 2) - pow(L23, 2));			//medians
	m2 = 0.5 * sqrt(2 * pow(L12, 2) + 2 * pow(L23, 2) - pow(L13, 2));
	m3 = 0.5 * sqrt(2 * pow(L13, 2) + 2 * pow(L23, 2) - pow(L12, 2));
	cout << "  Medians falling from points 1, 2, 3" << endl << "m1 = " << m1 << endl << "m2 = " << m2 << endl <<"m3 = " << m3 << endl;

	bis1 = (sqrt(L12 * L13 * (L12 + L13 + L23) * (L12 + L13 - L23))) / (L12 + L13);				//bisectors
	bis2 = (sqrt(L12 * L23 * (L12 + L13 + L23) * (L12 + L23 - L13))) / (L12 + L23);
	bis3 = (sqrt(L13 * L23 * (L13 + L12 + L23) * (L13 + L23 - L13))) / (L13 + L23);
	cout << "  Bisectors fallig from points 1, 2, 3" << endl << "bis1 = " << bis1 << endl << "bis2 = " << bis2 << endl << "bis3 = " << bis3 << endl;

    a3rad = acos((pow(L23, 2) + pow(L13, 2) - pow(L12, 2)) / (2 * L23 * L13));			//angles in rad
	a2rad = acos((pow(L23, 2) + pow(L12, 2) - pow(L13, 2)) / (2 * L23 * L12));
	a1rad = acos((pow(L13, 2) + pow(L12, 2) - pow(L23, 2)) / (2 * L13 * L12));
	cout << "  Angles in rad" << endl << "angle 1 = " << a1rad << endl << "angle 2 = " << a2rad << endl << "angle 3 = " << a3rad << endl;

	a1 = round((180 * a1rad) / pi);				//angles in degrees
	a2 = round((180 * a2rad) / pi);
	a3 = round((180 * a3rad) / pi);
	cout << "  Angles in degrees" << endl << "angle 1 = " << a1 << endl << "angle 2 = " << a2 << endl << "angle 3 = " << a3 << endl;

	R = L12 / (sin(a3rad) * 2);				//radius of circles
	r = S / p;
	cout << "  Radius of the circumference = " << R << endl << "  Radius of the circle inside the triangle = " << r << endl;

	C = 2 * pi * R;						//length and area of circles
	c = 2 * pi * r;
	Sofsmallcircle = pi * pow(R, 2);
	Sofbigcircle = pi * pow(r, 2);
	cout << "  Length of the circle around the triangle = " << C << endl << "  Length of the circle inside the triangle = " << c << endl;
	cout << "  Lrea of the circle around the triangle = " << Sofbigcircle << endl << "  Area of the circle inside the triangle = " << Sofsmallcircle << endl;

	P = L12 + L23 + L13;		//perimetr of the triangle
	cout << "  Perimetr of the triangle = " << P << endl;

	cout << "  Area of the triangle 1 = " << S << endl;
	S = (L12 * L23 * L13) / (4 * R);		//area type ¹2
	cout << "  Area of the triangle 2 = " << S << endl;
	S = L12 * L13 * sin(a1rad) * 0.5;		//area type ¹3
	cout << "  Area of the triangle 3 = " << S << endl;
	return 0;
}