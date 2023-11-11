#include<iostream>
#include<string>


using namespace std;

long double fact(int N)//function of factorial
{
	if (N == 0) 
		return 1;
	else 
		return N * fact(N - 1); 
}


int main() {

	cout << "This program displays the number of different anagrams that can be obtained from this word.";

	string s1, s2;

	getline(cin, s1);

	s2 = s1;

	int count = 1;
	long double prod = 1;

	for (int i = 0; i < s1.size(); i++)//for anagramms exists a formula, you can search for it in the net, here its realisation
	{
		for (int j = i + 1; j < s1.size(); j++)
		{
			if (s1[i] == s2[j])
			{
				count++;
				s2[j] = -1;
			}
		}

		prod *= fact(count);
		count = 1;
	}

	cout << endl << fact(s1.size()) / prod;
	return 0;
}