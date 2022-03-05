#include <iostream>
#include <iomanip>

using namespace std;

double getint()
{
    double a;
    bool x = false;
    cin >> a;
    if (a - round(a) == 0 && a > 0) {

    }
    else {
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
        else {
            x = true;
        }
    }return round(a);
}

double getint2()
{
    double a;
    bool x = false;
    cin >> a;
    if (a - round(a) == 0 && a > 0) {

    }
    else {
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
        else {
            x = true;
        }
    }return round(a);
}



///////////////////////////////main

int main() {

    cout << "You input a natural number n. The program counts the number of digits of the number n and determines which digit is in the digit with the number A  " << endl;
    cout << endl;
    int n;
    cout << "enter number n: ";
    n = getint();
    int b = 10;
    int* A = new int [b];
    
    int k = 0, i = 0, a;
    bool x = true;
    ///////////number of digits
    while(x)
    {
        if (n != 0) {
            A[i] = n % 10;
            n = (n - A[i]) / 10;
            i++;
        }
        if (n == 0) {
            x = false;
        }
    }
    cout << "only " << i << " digits among n" << endl;
    ///////////////////////////output an entered digit place
    cout << "enter digit A(A less than number of digits) and the program will output it" << endl << "enter number A: ";
    a = getint2();
    bool m = true;
    while (m) {
        if (a > i) {
            cout << endl << "this input is invalid, try again: ";
            a = getint2();
        }
        else {
            m = false;
        }
    }
    cout << "this number in the digit number " << a << " is: " << A[a - 1];
    
    delete [] A;

    return 0;
}