#include <fstream>
#include <iostream>
#include<string>
#include<iomanip>

using namespace std;
struct objects
{
	int number = 0;
	std::string name;
	std::string adress;
	std::string registration_date;
};

void Menu(objects* obj, int n);
void GetStructures(objects* obj, int n);
void ShowStructures(objects* obj, int n);
void AddStructure(objects* obj, int n);
void SortStructures(objects* obj, int n);
void ChangeStructure(objects* obj, int n);
void DeleteStructure(objects* obj, int n);
void FinalShowStructures(objects* obj, int n);
int GetInt();

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

int main() {
	printf("Enter number of products: ");
	int n = GetInt();

	objects* obj = new objects[n];

	GetStructures(obj, n);

	return 0;
}

void ShowStructures(objects* obj, int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << "Number of a " << i + 1 << " cumstomer: ";
		cout << obj[i].number;
		cout << std::endl;

		cout << "Name of " << i + 1 << " customer: ";
		cout << obj[i].name;
		cout << std::endl;

		cout << "Adress of " << i + 1 << " customer: ";
		cout << obj[i].adress;
		cout << std::endl;

		cout << "Registration date of " << i + 1 << " customer: ";
		cout << obj[i].registration_date;
		cout << std::endl << std::endl << std::endl;
	}

	cout << "Press any key to back to the menu : ";
	system("pause");
	system("cls");
	Menu(obj, n);
}

void GetStructures(objects* obj, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (fin.eof())
		{
			std::cout << "\nYou need to enter more information.\n";
			AddStructure(obj, i);
		}

		fin >> obj[i].number;
		

		string str1, str, str2;
		fin.ignore();
		getline(fin, str1);
		obj[i].name = str1;
		

		getline(fin, str);
		obj[i].adress = str;
		

		getline(fin, str2);
		obj[i].registration_date = str2;
		

	}
	SortStructures(obj, n);
}

void AddStructure(objects* obj, int n)
{
	cout << "Have you forgot something?" << std::endl;

	objects* obj1 = new objects[n + 1];
	for (int i = 0; i < n; i++)
	{
		obj1[i].number = obj[i].number;
		obj1[i].name = obj[i].name;
		obj1[i].adress = obj[i].adress;
		obj1[i].registration_date = obj[i].registration_date;
	}

	cout << "Number of " << n + 1 << " customer: ";
	cin.ignore();
	obj1[n].number = GetInt();
	cout << endl;

	string str1, str, str2;
	cout << "Name of " << n + 1 << " customer: ";
	cin.ignore();
	getline(cin, str1);
	obj1[n].name = str1;
	cout << endl;


	cout << "Adress of " << n + 1 << " customer: ";
	getline(cin, str);
	obj1[n].adress = str;
	cout << endl;

	cout << "Registration date of " << n + 1 << " customer: ";
	getline(cin, str2);
	obj1[n].registration_date = str2;
	cout << endl;

	Menu(obj1, n + 1);
}

void SortStructures(objects* obj, int n)
{
	objects* obj1 = new objects[n - 1];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (obj[i].name == obj[j].name && obj[i].adress == obj[j].adress && i != j)
			{
				int k = 0;
				for (; k < j; k++)
				{
					obj1[k] = obj[k];
				}
				for (int p = k + 1; p < n; p++)
				{
					obj1[p - 1] = obj[p];
				}
				delete[] obj;
				Menu(obj1, n - 1);
				
			}
		}
	}
	Menu(obj1, n);
}

void Menu(objects* obj, int n)
{
	cout << "1) " << "Show all the entered customers." << std::endl;
	cout << "2) " << "Add new customer." << std::endl;
	cout << "3) " << "Changing information about customer." << std::endl;
	cout << "4) " << "Deleting one of the customers." << std::endl;
	cout << "5) " << "Exit." << std::endl;

	cout << "Enter a number of a command you want me to do: ";

	int a;

	cin >> a;

	if (a == 1)
	{
		system("cls");
		ShowStructures(obj, n);
	}
	if (a == 2)
	{
		system("cls");
		AddStructure(obj, n);
	}
	if (a == 3)
	{
		system("cls");
		ChangeStructure(obj, n);
	}
	if (a == 4)
	{
		system("cls");
		DeleteStructure(obj, n);
	}
	if (a == 5)
	{
		system("cls");
		FinalShowStructures(obj, n);
		cout << "See you again.. " << std::endl;
		exit(0);
	}
}

void ChangeStructure(objects* obj, int n)
{
	int a;
	cout << "War never changes..    But i will help you to change info about your products" << std::endl;
	cout << "Enter a name of product you want to change, because its impossible to find something if we dont know it's name: ";
	a = GetInt();

	bool b = true;
	int i = 0;

	for (; i < n; i++)
	{
		if (obj[i].number == a)
		{
			cout << std::endl << "I found it, thats it: " << std::endl;

			cout << "Serial number of a customer: ";
			cout << obj[i].number;
			cout << std::endl;

			cout << "Name of a customer: ";
			cout << obj[i].name;
			cout << std::endl;

			cout << "Adress of a customer: ";
			cout << obj[i].adress;
			cout << std::endl;

			cout << "Registration date of a customer: ";
			cout << obj[i].registration_date;
			cout << std::endl << std::endl;

			b = false;
			break;
		}
	}
	if (b)
	{
		cout << "I didnt find such product :(  You can press any key to back to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}

	cout << "Okay, now you should remind me, what do you want to change here, \nHere a list of options you can do. Look carefully " << std::endl << std::endl;
	cout << "1) " << "Changing the number of the customer." << std::endl;
	cout << "2) " << "Changing the name of the customer." << std::endl;
	cout << "3) " << "Changing the adress of a customer" << std::endl;
	cout << "4) " << "Changing a serial number of a customer" << std::endl;
	cout << "5) " << "My apartment is on fire, i need to go out" << std::endl;

	int c;
	cout << std::endl << "I thought you would read it for the rest of my life, now just enter the number of function you you want me to do: ";
	c = GetInt();

	if (c == 1)
	{
		cout << std::endl << "Here we go!" << std::endl << std::endl << "Enter new Number of a customer(there is no turning back(no,it is, just enter zero(0))): ";
		int d = GetInt();


		if (d == 0)
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[i].number = d;
			cout << std::endl << "Work is done, im bored, letsgo to the menu, but at start we will see our 'new' product: " << std::endl << std::endl;

			cout << "Number of the customer: ";
			cout << obj[i].number;
			cout << std::endl;

			cout << "Name of the customer: ";
			cout << obj[i].name;
			cout << std::endl;

			cout << "Adress of the customer: ";
			cout << obj[i].adress;
			cout << std::endl;

			cout << "Registration date of the customer: ";
			cout << obj[i].registration_date;
			cout << std::endl << std::endl;

			fout << std::endl << "Press any key to go to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	else if (c == 2)
	{
		std::string str4 = "";
		cout << std::endl << "Here we go!" << std::endl << std::endl << "Enter new Name of the customer(there is no turning back(no,it is, just enter nothing)): ";
		cin.ignore();
		getline(cin, str4);
		if (str4 == "")
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[i].name = str4;
			cout << std::endl << "Letsgo to the menu, but at start we will see our 'new' customer: " << std::endl;

			cout << "Number of the customer: ";
			cout << obj[i].number;
			cout << std::endl;

			cout << "Name of the customer: ";
			cout << obj[i].name;
			cout << std::endl;

			cout << "Adress of the customer: ";
			cout << obj[i].adress;
			cout << std::endl;

			cout << "Registration date of the customer: ";
			cout << obj[i].registration_date;
			cout << std::endl << std::endl;

			cout << std::endl << "Press any key to go to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	else if (c == 3)
	{
		std::string str3 = "";
		cout << std::endl << "Here we go!" << std::endl << std::endl << "Enter new Adress of the customer(there is no turning back(no,it is, just enter nothing)): ";
		cin.ignore();
		getline(cin, str3);
		if (str3 == "")
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[i].adress = str3;
			cout << std::endl << "Letsgo to the menu, but at start we will see our 'new' customer: " << std::endl;
		}

		cout << "Number of the customer: ";
		cout << obj[i].number;
		cout << std::endl;

		cout << "Name of the customer: ";
		cout << obj[i].name;
		cout << std::endl;

		cout << "Adress of the customer: ";
		cout << obj[i].adress;
		cout << std::endl;

		cout << "Registration date of the customer: ";
		cout << obj[i].registration_date;
		cout << endl << endl;

		cout << endl << "Press any key to go to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);

	}
	else if (c == 4)
	{
		std::string str2 = "";
		cout << std::endl << "Here we go!" << std::endl << std::endl << "Enter new Registration adress(there is no turning back(no,it is, just enter nothing)): ";
		cin.ignore();
		getline(cin, str2);
		if (str2 == "")
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[i].name = str2;
			cout << std::endl << "Letsgo to the menu, but at start we will see our 'new' customer: " << std::endl;
		}

		cout << "Number of the customer: ";
		cout << obj[i].number;
		cout << std::endl;

		cout << "Name of the customer: ";
		cout << obj[i].name;
		cout << std::endl;

		cout << "Adress of the customer: ";
		cout << obj[i].adress;
		cout << std::endl;

		cout << "Registration date of the customer: ";
		cout << obj[i].registration_date;
		cout << endl << endl;

		cout << endl << "Press any key to go to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}
	else if (c == 5)
	{
		FinalShowStructures(obj, n);
		exit(0);
	}else
	{
		cout << std::endl << "You missed the keyboard, we are  going to the menu. Press any key to go to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}
}

int GetInt()
{
	double a;
	bool x = false;
	cin >> a;
	if (a - round(a) == 0 && (a >= 1 || a == 0)) {

	}
	if ((a < 1 && a != 0) || a - round(a) != 0) {
		x = true;
	}
	while (cin.fail() || x) {
		cin.clear();
		cin.ignore(4000, '\n');
		cout << "this input is invalid, try again: ";
		cin >> a;
		cout << endl;
		if (a - round(a) == 0 && (a >= 1 || a == 0)) {
			x = false;
		}
		if ((a < 1 && a != 0) || a > 6 || a - round(a) != 0) {
			x = true;
		}
	}return a;
}

void DeleteStructure(objects* obj, int n)
{
	cout << "Wanna delete a customer from the list? Thats not a problem.\nEnter a Number of a customer you want to delete, and i will try my best: ";
	int s = GetInt();

	objects* obj1 = new objects[n - 1];

	int a = -1;
	bool b = true;
	for (int i = 0; i < n; i++)
	{
		if (obj[i].number == s)
		{
			a = i;
			b = false;
		}
	}
	if (b)
	{
		cout << "I didnt find such customer, backing to main menu :(  ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}
	for (int j = 0; j < a; j++)
	{
		obj1[j] = obj[j];
	}
	for (int i = a + 1; i < n; i++)
	{
		obj1[i - 1] = obj[i];
	}
	delete[] obj;
	cout << std::endl << "Deleting is done, we can go to main menu, press any key: ";
	system("pause");
	system("cls");
	Menu(obj1, n - 1);
}

void FinalShowStructures(objects* obj, int n)
{
	for (int i = 0; i < n; i++)
	{
		fout << "Number of a " << i + 1 << " cumstomer: ";
		fout << obj[i].number;
		fout << std::endl;

		fout << "Name of " << i + 1 << " customer: ";
		fout << obj[i].name;
		fout << std::endl;

		fout << "Adress of " << i + 1 << " customer: ";
		fout << obj[i].adress;
		fout << std::endl;

		fout << "Registration date of " << i + 1 << " customer: ";
		fout << obj[i].registration_date;
		fout << std::endl << std::endl << std::endl;
	}
}