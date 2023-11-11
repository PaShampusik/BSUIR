#include<iostream>
#include<stdio.h>
#include<string>
#include<iomanip>


struct objects
{
	std::string name;
	std::string date;
	int status = 1;
	int date_of_manufacture = 0;
};

void Menu(objects* obj, int n);
void GetStructures(objects* obj, int n);
void ShowStructures(objects* obj, int n);
void AddStructure(objects* obj, int n);
void SortStructures(objects* obj, int n);
void FindProduct(objects* obj, int n);
void ChangeStructure(objects* obj, int n);
void DeleteStructure(objects* obj, int n);
int GetInt();
int GetInt012();

int main()
{
	printf("Enter number of products: ");
	int n = GetInt();

	objects* obj = new objects[n];

	std::cout << "Okay, now lets fill the blanks for each of product: " << std::endl;
	GetStructures(obj, n);

	return 0;
}

void ShowStructures(objects* obj, int n)
{
	std::cout << "Wanna see something?" << std::endl;
	system("pause");

	for (int i = 0; i < n; i++)
	{
		std::cout << "Name of " << i + 1 << " product: ";
		std::cout << obj[i].name;
		std::cout << std::endl;

		std::cout << "Date of acceptance for repair of " << i + 1 << " product: ";
		std::cout << obj[i].date;
		std::cout << std::endl;

		std::cout << "Readiness of repair of " << i + 1 << " product: ";
		std::cout << obj[i].status;
		std::cout << std::endl;

		std::cout << "Date of manufacture of " << i + 1 << " product: ";
		std::cout << obj[i].date_of_manufacture;
		std::cout << std::endl << std::endl << std::endl;
	}

	std::cout << "Okay, if you still see nothing above, you have some problems with your eyes, press any key to back to the menu: ";
	system("pause");
	system("cls");
	Menu(obj, n);
}

void GetStructures(objects* obj, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::string str, str1;
		std::cout << "Name of " << i + 1 << " product: ";
		std::cin.ignore();
		getline(std::cin, str);
		obj[i].name = str;
		std::cout << std::endl;


		std::cout << "Date of acceptance for repair of " << i + 1 << " product: ";
		getline(std::cin, str1);
		obj[i].date = str1;
		std::cout << std::endl;


		std::cout << "Readiness of repair of " << i + 1 << " product(0 if it is not ready, 1 if it is ready, 2 if product is on client): ";
		obj[i].status = GetInt012();
		std::cout << std::endl;

		std::cout << "Year of manufacture of " << i + 1 << " product: ";
		obj[i].date_of_manufacture = GetInt();
		std::cout << std::endl;
	}
	std::cout << "You got some products, congratulations, but why are you staring at them? Lets do something with them (-__-), press any keys to back to the menu: ";
	system("pause");
	system("cls");
	Menu(obj, n);
}

void AddStructure(objects* obj, int n)
{
	std::cout << "Have you forgot something?" << std::endl;

	objects* obj1 = new objects[n + 1];
	for (int i = 0; i < n; i++)
	{
		obj1[i].name = obj[i].name;
		obj1[i].date = obj[i].date;
		obj1[i].status = obj[i].status;
		obj1[i].date_of_manufacture = obj[i].date_of_manufacture;
	}

	std::string str, str1;

	std::cout << "Name of " << n + 1 << " product: ";
	std::cin.ignore();
	getline(std::cin, str);
	obj1[n].name = str;
	std::cout << std::endl;

	std::cout << "Date when product came to repair centre of " << n + 1 << " product: ";
	std::cin.ignore();
	getline(std::cin, str1);
	obj1[n].date = str1;
	std::cout << std::endl;

	std::cout << "Readiness of repair of " << n + 1 << " product(0 - is not ready, 1 - ready, 2 - on client): ";
	obj1[n].status = GetInt012();
	std::cout << std::endl;

	std::cout << "Date of manufacture of " << n + 1 << " product: ";
	std::cin >> obj1[n].date_of_manufacture;
	std::cout << std::endl;

	std::cout << "You got some products, congratulations, but why are you staring at them? Lets do something with them (-__-), press any keys to got to the menu: ";
	system("cls");
	delete[] obj;
	Menu(obj1, n + 1);
	
}

void SortStructures(objects* obj, int n)
{
	std::cout << "You want to sort your productes by status? Wise move, lets do it: " << std::endl << std::endl;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (obj[j].status < obj[j + 1].status)
			{
				objects temp = obj[j];
				obj[j] = obj[j + 1];
				obj[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << ") " << std::setw(15) << "Name of product: " << obj[i].name;

		if (obj[i].status == 0)
		{
			std::cout << "              Status: Not ready" << std::endl;
		}
		if (obj[i].status == 1)
		{
			std::cout << "              Status: Ready" << std::endl;
		}
		if (obj[i].status == 2)
		{
			std::cout << "              Status: On client" << std::endl;
		}
	}
	std::cout << std::endl << "Now you can see a list of sorted products by their names and statuses, idk, why do you need it, but it is above :D" << std::endl;

	std::cout << "If you are satisfied by my sort alogitm, you can press any key to back to the menu: ";
	system("pause");
	system("cls");
	Menu(obj, n);
}

void Menu(objects* obj, int n)
{
	std::cout << "1) " << "Show all the entered products." << std::endl;
	std::cout << "2) " << "Sorting by readiness of the products." << std::endl;
	std::cout << "3) " << "Add new product." << std::endl;
	std::cout << "4) " << "Find product by the name." << std::endl;
	std::cout << "5) " << "Changing information about product." << std::endl;
	std::cout << "6) " << "Deleting one of products." << std::endl;
	std::cout << "7) " << "Exit." << std::endl;

	std::cout << "Enter a number of a command you want me to do: ";

	int a;

	std::cin >> a;

	if (a == 1)
	{
		system("cls");
		ShowStructures(obj, n);
	}
	if (a == 2)
	{
		system("cls");
		SortStructures(obj, n);
	}
	if (a == 3)
	{
		system("cls");
		AddStructure(obj, n);
	}
	if (a == 4)
	{
		system("cls");
		FindProduct(obj, n);
	}
	if (a == 5)
	{
		system("cls");
		ChangeStructure(obj, n);
	}
	if (a == 7)
	{
		system("cls");
		std::cout << "See you again.. " << std::endl;
		exit(0);
	}
	if (a == 6)
	{
		system("cls");
		DeleteStructure(obj, n);
	}
}

void FindProduct(objects* obj, int n)
{
	std::string str;
	std::cout << "Enter name of product, you want to find: ";
	std::cin.ignore();
	getline(std::cin, str);

	bool a = true;

	for (int i = 0; i < n; i++)
	{
		if (obj[i].name == str)
		{
			std::cout << "I find it, thats it: " << std::endl << std::endl;

			std::cout << "Name of product: ";
			std::cout << obj[i].name;
			std::cout << std::endl;

			std::cout << "Date of acceptance for repair of product: ";
			std::cout << obj[i].date;
			std::cout << std::endl;

			std::cout << "Readiness of repair of product: ";
			std::cout << obj[i].status;
			std::cout << std::endl;

			std::cout << "Date of manufacture of the product: ";
			std::cout << obj[i].date_of_manufacture;
			std::cout << std::endl << std::endl;

			a = false;
			std::cout << "Are you bored? You can press any key to back to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	if (a)
	{
		std::cout << "I didnt find such product :(  You can press any key to back to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}
}

void ChangeStructure(objects* obj, int n)
{
	std::string str;
	std::cout << "War never changes..    But i will help you to change info about your products" << std::endl;
	std::cout << "Enter a name of product you want to change, because its impossible to find something if we dont know it's name: ";
	std::cin >> str;

	bool a = true;
	int c = 0;

	for (int i = 0; i < n; i++)
	{
		if (obj[i].name == str)
		{
			std::cout << std::endl << "I found it, thats it: " << std::endl;

			std::cout << "Name of product: ";
			std::cout << obj[i].name;
			std::cout << std::endl;

			std::cout << "Date of acceptance for repair of product: ";
			std::cout << obj[i].date;
			std::cout << std::endl;

			std::cout << "Readiness of repair of product: ";
			std::cout << obj[i].status;
			std::cout << std::endl;

			std::cout << "Date of manufacture of the product: ";
			std::cout << obj[i].date_of_manufacture;
			std::cout << std::endl << std::endl;

			c = i;
			a = false;
		}
	}
	if (a)
	{
		std::cout << "I didnt find such product :(  You can press any key to back to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}

	std::cout << "Okay, now you should remind me, what do you want to change here, \nHere a list of options you can do. Look carefully " << std::endl << std::endl;
	std::cout << "1) " << "Changing the name of the product.   Only 0 people change their name during life." << std::endl;
	std::cout << "2) " << "Changing the date when product came to the repairing centre.  P.S. omg, how can it be changed?" << std::endl;
	std::cout << "3) " << "Wanna change status of repairing? God bless you, my laptop is done." << std::endl;
	std::cout << "4) " << "Date of manufacture. The date of the invention of the computer has not changed since 1927, nvm" << std::endl;
	std::cout << "5) " << "Nevermind, i forgot what i wanted to do, back me to the Menu" << std::endl;
	std::cout << "6) " << "My apartment is on fire, i need to go out" << std::endl;

	int b;
	std::cout << std::endl << "I thought you would read it for the rest of my life, now just enter the number of function you you want me to do: ";
	b = GetInt();

	if (b == 1)
	{
		std::string str2 = " ";
		std::cout << std::endl << "Here we go!" << std::endl  << std::endl << "Enter new NAME of product(there is no turning back(no,it is, just enter nothing)): ";
		std::cin.ignore();
		getline(std::cin, str2);
		if (str2 == "")
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[c].name = str2;
			std::cout << std::endl << "Work is done, im bored, letsgo to the menu, but at start we will see our 'new' product: " << std::endl << std::endl;

			std::cout << "Name of product: ";
			std::cout << obj[c].name;
			std::cout << std::endl;

			std::cout << "Date of acceptance for repair of product: ";
			std::cout << obj[c].date;
			std::cout << std::endl;

			std::cout << "Readiness of repair of product: ";
			std::cout << obj[c].status;
			std::cout << std::endl;

			std::cout << "Date of manufacture of the product: ";
			std::cout << obj[c].date_of_manufacture;
			std::cout << std::endl << std::endl;

			std::cout << std::endl << "Press any key to go to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	if (b == 2)
	{
		std::string str4 = " ";
		std::cout << std::endl << "Here we go!" << std::endl << std::endl << "Enter new date when product came to the repairing centre(there is no turning back(no,it is, just enter nothing)): ";
		std::cin.ignore();
		getline(std::cin, str4);
		if (str4 == "")
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[c].date = str4;
			std::cout << std::endl << "Letsgo to the menu, but at start we will see our 'new' product: " << std::endl;

			std::cout << "Name of product: ";
			std::cout << obj[c].name;
			std::cout << std::endl;

			std::cout << "Date of acceptance for repair of product: ";
			std::cout << obj[c].date;
			std::cout << std::endl;

			std::cout << "Readiness of repair of product: ";
			std::cout << obj[c].status;
			std::cout << std::endl;

			std::cout << "Date of manufacture of the product: ";
			std::cout << obj[c].date_of_manufacture;
			std::cout << std::endl << std::endl;

			std::cout << std::endl << "Press any key to go to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	if (b == 3)
	{
		int num = -1;
		std::cout << "Here we go!" << std::endl << "Enter new  status of repairing(0 - not ready, 1 - ready, 2 - on client): ";
		num = GetInt012();

		if (num == 2)
		{
			system("cls");
			Menu(obj, n);
		}
		obj[c].date = num;
		std::cout << std::endl << "Letsgo to the menu, but at start we will see our 'new' product: " << std::endl;

		std::cout << "Name of product: ";
		std::cout << obj[c].name;
		std::cout << std::endl;

		std::cout << "Date of acceptance for repair of product: ";
		std::cout << obj[c].date;
		std::cout << std::endl;

		std::cout << "Readiness of repair of product: ";
		std::cout << obj[c].status;
		std::cout << std::endl;

		std::cout << "Date of manufacture of the product: ";
		std::cout << obj[c].date_of_manufacture;
		std::cout << std::endl << std::endl;

		std::cout << std::endl << "Press any key to go to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);

	}
	if (b == 4)
	{
		std::cout << "Here we go!" << std::endl << "Enter new year of manufacture(there is no turning back(no,it is, just enter 0)): ";
		int num1 = GetInt();

		if (num1 == 0)
		{
			system("cls");
			Menu(obj, n);
		}
		else
		{
			obj[c].date_of_manufacture = num1;
			std::cout << std::endl << "Lets go to the menu, but at start we will see our 'new' product: " << std::endl;

			std::cout << "Name of product: ";
			std::cout << obj[c].name;
			std::cout << std::endl;

			std::cout << "Date of acceptance for repair of product: ";
			std::cout << obj[c].date;
			std::cout << std::endl;

			std::cout << "Readiness of repair of product: ";
			std::cout << obj[c].status;
			std::cout << std::endl;

			std::cout << "Date of manufacture of the product: ";
			std::cout << obj[c].date_of_manufacture;
			std::cout << std::endl << std::endl;

			std::cout << std::endl << "Press any key to go to the menu: ";
			system("pause");
			system("cls");
			Menu(obj, n);
		}
	}
	if (b == 5)
	{
		system("cls");
		Menu(obj, n);
	}

	if (b == 6)
	{
		exit(0);
	}
	if (b < 1 && b > 6)
	{
		std::cout << std::endl << "You missed the keyboard, we are  going to the menu. Press any key to go to the menu: ";
		system("pause");
		system("cls");
		Menu(obj, n);
	}
}

int GetInt()
{
	double a;
	bool x = false;
	std::cin >> a;
	if (a - round(a) == 0) {

	}
	if (a < 1 || a - round(a) != 0) {
		x = true;
	}
	while (std::cin.fail() || x) {
		std::cin.clear();
		std::cin.ignore(4000, '\n');
		std::cout << "this input is invalid, try again: ";
		std::cin >> a;
		std::cout << std::endl;
		if (a - round(a) == 0) {
			x = false;
		}
		if (a < 1 || a - round(a) != 0) {
			x = true;
		}
	}return a;
}

int GetInt012()
{
	double a;
	bool x = false;
	std::cin >> a;
	if (a - round(a) == 0 && (a == 0 || a == 1 || a == 2)) {

	}
	if ((a != 1 && a != 0 && a != 2) || a - round(a) != 0) {
		x = true;
	}
	while (std::cin.fail() || x) {
		std::cin.clear();
		std::cin.ignore(4000, '\n');
		std::cout << "this input is invalid, try again: ";
		std::cin >> a;
		std::cout << std::endl;
		if (a - round(a) == 0 && (a == 0 || a == 1 || a == 2)) {
			x = false;
		}
		if ((a != 1 && a != 0 && a != 2) || a - round(a) != 0) {
			x = true;
		}
	}return a;
}

void DeleteStructure(objects* obj, int n) 
{
	std::cout << "Wanna delete a repaired product? Thats not a problem.\nEnter a NAME of a product you want to delete, and i will try my best: ";
	std::string s = "";
	std::cin.ignore();
	getline(std::cin, s);

	objects* obj1 = new objects[n - 1];

	int a = -1;
	bool b = true;
	for (int i = 0; i < n; i++)
	{
		if (obj[i].name == s)
		{
			a = i;
			b = false;
		}
	}
	if (b)
	{
		std::cout << "I didnt find such product, backing to main menu :(  ";
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
	std::cout << std::endl << "Deleting is done, we can go to main menu, press any key: ";
	system("pause");
	system("cls");
	Menu(obj1, n - 1);
}