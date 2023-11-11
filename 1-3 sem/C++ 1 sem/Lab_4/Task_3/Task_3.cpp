#include <iostream>
#include <iomanip>

using namespace std;

double getint()
{
    double a;
    bool x = false;
    cin >> a;
    if (a - round(a) == 0 && a - ((int)a / 2) * 2 == 1) {

    }
    else if (a - (a / 2) * 2 != 1){
        x = true;
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
    if(a - round(a) == 0 && a - ((int)a / 2) * 2 == 1) {
        x = false;
    }
    else if (a - (a / 2) * 2 != 1) {
    x = true;
    }
    else {
    x = true;
    }
    }return round(a);
}

double getdouble()
{
    double a;
    bool x = false;
    cin >> a;

    while (cin.fail() || x) {

        cin.clear();
        cin.ignore(4000, '\n');
        cout << "this input is invalid, try again: ";
        cin >> a;
        cout << endl;

    }return a;
}
///////////////////////////////main

int main() {
       
    cout << "this program will find the smallest and largest values ​​in the shaded part of the square matrix of a matrix (see figure C), the dimension n of the matrix is ​​odd";
    cout << endl;
    int n;
    cout << "enter number n: ";
    n = getint();
    double** A = new double* [n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "enter A [" << i << "][" << j << "]: ";
            A[i][j] = getdouble();
            cout << endl;
        }
        
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << A[i][j];
        }
        cout << endl;
    }

    //////////////////////////////////calculating min and max
    
    double max = -1000000000;
    double min = 1000000000;
    int k = 1, l = 0;


    //////////finding minimum and maximum in accessed area

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= (n - 1) / 2; j++)
        {
            
            if (i > j) {
                if (A[i][j] < min) {
                        min = A[i][j];
                }
                if (A[i][j] > max) {
                        max = A[i][j];
                }
            }
        }
    }
    for (int j = n - 1; j > (n - 1) / 2; j--)
    {
        for (int i = k; i < n; i++)
        {
            if (A[i][j] < min) {
                min = A[i][j];
            }
            if (A[i][j] > max) {
                max = A[i][j];
            }
        }
        k++;
    }
                
    
        

    cout << endl << "max element is: " << max << endl;
    cout << endl << "min element is: " << min << endl;




    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;
    return 0;
}