#include<iostream>
#include<vector>

int main() {
	int x = 7;
	int y = x++ + ++x * 2;
	int c = x++ + 23 * 2;


    std:: cout << y << "                  " << c << std::endl;
}