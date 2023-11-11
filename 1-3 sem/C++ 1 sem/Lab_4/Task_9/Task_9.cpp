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

int main()
{

    cout << "This program will calculate the matrix product, if possible :D " << endl;


    int k, m, n, q, sum;
    cout << "Enter first size of the 1-st matrix: ";
    k = getint();
    cout << endl << "Enter second size of the 1-st matrix: ";
    m = getint();
    cout << endl << "Enter first size of the 2-nd matrix: ";
    q = getint();
    cout << endl << "Enter second size of the 2-nd matrix: ";
    n = getint();


    int** Matrix1 = new int* [k];
    for (int i = 0; i < k; i++)
    {
        Matrix1[i] = new int[m];
    }
    int** Matrix2 = new int* [q];
    for (int i = 0; i < q; i++)
    {
        Matrix2[i] = new int[n];
    }

  
    //////////////////can be multiplied
    
    if (q == m) {
        int** Matrix3 = new int* [k];
        for (int i = 0; i < k; i++)
        {
            Matrix3[i] = new int[n];
        }

        
        for (int i = 0; i < k; i++)//////////////entering marix 1 and 2
        {
            for (int j = 0; j < m; j++)
            {
                cout << "element of Matrix1 A[" << i << "][" << j << "] is: ";
                Matrix1[i][j] = getint();
            }           
        }
        
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << "element of Matrix2 A[" << i << "][" << j << "] is: ";
                Matrix2[i][j] = getint();
            }          
        }

        cout << endl << "this is first matrix: " << endl;

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << setw(4) << Matrix1[i][j];
            }
            cout << endl;
        }

        cout << endl << "this is second matrix: " << endl;

        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(4) << Matrix2[i][j];
            }
            cout << endl;
        }

        cout << endl << "this is matrix we wanted to get: " << endl;
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum = 0;
                for (int r = 0; r < m; r++)
                {
                    sum += Matrix1[j][r] * Matrix2[r][i];
                }
                Matrix3[i][j] = sum;
                cout << setw(4) << Matrix3[i][j];
            }
            cout << endl;
            
        }
        for (int i = 0; i < k; i++)             ////////////deleting arrays
        {
            delete[] Matrix1[i];
        }
        delete[] Matrix1;

        for (int i = 0; i < q; i++)
        {
            delete[] Matrix2[i];
        }
        delete[] Matrix2;

        for (int i = 0; i < k; i++)
        {
            delete[] Matrix3[i];
        }
        delete[] Matrix3;
        
    }
    else {                  ///////////////cant be multiplied
        cout << endl << "this two matrix cant be multiplied";
    }
    return 0;
}