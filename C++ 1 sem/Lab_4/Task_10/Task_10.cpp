#include <iostream>
#include <iomanip>

using namespace std;


/////////////////this program generates magic sqare 3x3, you can place any odd integer instead of n in the program
int main()                                                                                                //
{                                                                                                         //
    const int n = 5; //<<----------------------------------------------------------------------------right there
    int MagicSquare[n][n];

    //////////////// set all slots as 0
    memset(MagicSquare, 0, sizeof(MagicSquare));

    ///////// position for 1
    int i = n / 2;
    int j = n - 1;

    //////////////// One by one put all values in magic square
    for (int k = 1; k <= n * n;) {

        if (i == -1 && j == n) 
        {
            j = n - 2;
            i = 0;
        }
        else {

            if (j == n) {
                j = 0;
            }

            if (i < 0) {
                i = n - 1;
            }
        }
        if (MagicSquare[i][j]) 
        {
            j -= 2;
            i++;
            continue;
        }
        else {
            MagicSquare[i][j] = k++; ////////////// set number
        }
        j++;
        i--; 
    }

   
    cout << "The Magic Square for n = 3" << ":\nSum of each row or column " << n * (n * n + 1) / 2 << ":\n\n";
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            cout << setw(4) << MagicSquare[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


