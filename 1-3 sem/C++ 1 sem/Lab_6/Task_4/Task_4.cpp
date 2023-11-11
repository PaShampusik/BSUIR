#include <iostream>
#include <string>

using namespace std;

int main() {

	cout << "April 1, 20 ?? the reform of the English language will be carried out,allowing to facilitate its development by foreigners and Englishschoolchildren.First, the four letters C, Q, Wand X will be removed from the alphabet(by computer keyboard instead of them there will be keys that call programs Word, eXcel and others).Instead of c before the letters e, i, y, you will need to write the letter s, and otherwise the letter k.Instead of the letter q, you will need to write the letter k, instead of the combination qu - kv, instead of x - ks, and instead of w - v.Second, the combination of ph will be written as f, youand oo as u, ee as i, th as z.In addition, all double consonants(including those formed after substitutions), causing great difficulties for students, will become single, for example, apple after reforms should be written as aple.This program will carry out this reform for the entered text." << endl;

	string s;

	//array for double letters

	char consonants[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

	getline(cin, s);

	for (int i = 0; i < s.size(); i++)
	{


		if (s[i] == 'c' || s[i] == 'C')
		{
			if (s[i + 1] == 'e' || s[i + 1] == 'i' || s[i + 1] == 'y')
			{
				s[i] = 's';
			}

			else
			{
				s[i] = 'k';
			}
			i -= 1;
		}


		if (s[i] == 'q' || s[i] == 'Q')
		{
			if (s[i + 1] == 'u')
			{
				s[i] = 'k';
				s[i + 1] = 'v';
			}
			else {
				s[i] = 'k';
			}
			i -= 1;
		}


		if (s[i] == 'x' || s[i] == 'X')
		{
			s.replace(i, 1, "ks");
			i -= 1;
		}


		if (s[i] == 'w' || s[i] == 'W')
		{
			s[i] = 'v';
		}
		

		if ((s[i] == 'p' || s[i] == 'P') && s[i + 1] == 'h')
		{
			if (s[i] == 'p')
			{
				s.replace(i, 2, "f");
			}

			if (s[i] == 'P')
			{
				s.replace(i, 2, "F");
			}
			i -= 1;
		}

		if ((s[i] == 'y' || s[i] == 'Y') && s[i + 1] == 'o' && s[i + 2] == 'u')
		{
			if (s[i] == 'y')
			{
				s.replace(i, 3, "oo");
			}

			if (s[i] == 'Y')
			{
				s.replace(i, 3, "Oo");
			}
		}

		if (s[i] == 'o' && s[i + 1] == 'o')
		{
			s.replace(i, 2, "u");
		}

		if (s[i] == 'e' && s[i + 1] == 'e')
		{
			s.replace(i, 2, "i");
		}

		if ((s[i] == 't' || s[i] == 'T') && s[i + 1] == 'h')
		{
			if (s[i] == 'T')
			{
				s.replace(i, 2, "Z");
			}

			if (s[i] == 't')
			{
				s.replace(i, 2, "z");
			}
			i -= 1;
		}

		//replacing of double letters

		for (int j = 0; j < 21; j++)
		{
			if (consonants[j] == s[i] && consonants[j] == s[i + 1])
			{
				s.replace(i, 2, 1, s[i]);
			}
		}
	}

	cout << s;




	return 0;
}