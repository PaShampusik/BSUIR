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



///////////////////////////////main

int main() {

    cout << "this program will replace with zeros all elements that are in the cells between nearest minimum and maximum elements (not including them). If after this action most of the array contains zeros, it will remove all zero elements from the array (preserving the order of the remaining elements)." << endl;
    cout << "enter number of members of array:  ";
    int n = getint();

    int* Array = new int [n];
    

    for (int i = 0; i < n; i++) {
        
        cout << "enter element " <<  i + 1<< ":  ";
            Array[i] = getint();
        }
    int max = -100000, min = 100000, M = -1, m = -1;
    for (int i = 0; i < n; i++)
    {
        if (Array[i] > max) {
            max = Array[i];
            M = i;
        }if (Array[i] < min) {
            min = Array[i];
            m = i;
        }
    }
    cout << endl << "start array is : " << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(5) << Array[i];
    }

    /////////////////////////////////////new array 
    int b = m, a = M;
    if (fabs(m - M) - 1 > n / 2) {
        int* Array2 = new int[n - m - M + 1];

        /////////manimum is far than maximum

        if (m > M) {
            for (int i = 0; i <= M; i++)
            {
                Array2[i] = Array[i];
            }
            for (int i = M + 1; i < n - (m - M - 1); i++)
            {
                Array2[i] = Array[b];
                b++;
            }
            cout << endl << "this is final array: ";
            for (int i = 0; i < n - (m - M - 1); i++)
            {
                cout << setw(5) << Array2[i];
            }
        }

        /////////maximum is far than minimum

        if (M > m) {     
            for (int i = 0; i <= m; i++)
            {
                Array2[i] = Array[i];
            }
            for (int i = m + 1; i < n - (M - m - 1); i++)
            {
                Array2[i] = Array[a];
                a++;
            }
            cout << endl << "this is final array: ";
            for (int i = 0; i < n - (M - m - 1); i++)
            {
                cout << setw(5) << Array2[i];
            }
        }
        delete[] Array2;

    }
    else {////////////////////////////////////no new array(number between maximum and minimum is less than half of n
        for (int i = 0; i < n; i++)
        {
            if (M > m) {
                if (i > m && i < M) {
                    Array[i] = 0;
                }
            }
            if (m > M) {
                if (i > M && i < m) {
                    Array[i] = 0;
                }
            }
        }
        cout << endl << "this is final array: ";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << Array[i];
        }
    }

    delete[] Array;
    

    return 0;
}