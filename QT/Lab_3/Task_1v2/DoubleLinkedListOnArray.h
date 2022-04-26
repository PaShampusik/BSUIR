#ifndef DOUBLELIST_H
#define DOUBLELIST_H


#include "Vector.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>



class DoubleLinkedListOnArray {
private:
	struct Node {
		Staff product;
		int next = 0;
		int prev = 0;
		Node(){}
		Node(Staff pr, int n, int p)
			:product(pr), next(n), prev(p)
		{}
		~Node() {
		}
		bool compairingSurnames(QString name) {
			bool k = 1;
			int i = 0;
			while (product.getname().toStdString()[i] != ' ' && i < min(product.getname().toStdString().length(), name.length())) {
				if (product.getname().toStdString()[i] == name.toStdString()[i]) {}
				else
				{
					k = 0;
					return k;
				}
				++i;
			}
			return 1;
		}

		int min(int a, int b) {
			if (a < b) return a;
			else return b;
		}
	};

public:
	vector<Node> nodes;
	int head = 0;
	int tail = 0;
	DoubleLinkedListOnArray() {
		head = -1;
		tail = -1;
	}


	~DoubleLinkedListOnArray() {
		clear();
	}

	void clear() {
		while (nodes.size != 0) {
			nodes.pop_back();
		}
		head = -1;
		tail = -1;
	}
	int getSize() {
		return nodes.size;
	}

	void add(Staff product) {
		if (nodes.size == 0) {
			head = 0;
			tail = 0;
			nodes.push_back(Node(product, -1, 1));
		}
		else {
			nodes.push_back(Node(product, nodes.size - 1, nodes.size + 1));
			nodes[nodes.size - 2].next = nodes.size - 1;
			nodes[nodes.size - 1].prev = nodes.size - 2;
			nodes[nodes.size - 1].next = -1;
			tail = nodes.size - 1;
		}


	}

	void pop() {
		if (nodes.size == 0) {
			return;
		}
		if (nodes.size == 1) {
			head = -1;
			tail = -1;
			nodes.pop_back();
			return;
		}

		tail = nodes[tail].prev;
		nodes[tail].next = -1;
		nodes.pop_back();		
	}

	int getHead() {
		return head;
	}
	int getTail() {
		return tail;
	}

	Staff getProduct(int index) {
		return nodes[index].product;
	}

	DoubleLinkedListOnArray& operator=(const DoubleLinkedListOnArray& other) {
		if (this != &other) {
			nodes = other.nodes;
			head = other.head;
			tail = other.tail;
		}
		return *this;
	}

	void print() {
		int index = head;
		while (index != -1) {
			//std::cout << nodes[index].product.name << " " << nodes[index].product.count << " " << nodes[index].product.price << " " << nodes[index].product.date << std::endl;
			index = nodes[index].next;
		}
	}

	void SortByNumber()
	{
		Node temp;
		for (int i = 0; i < nodes.size - 1; i++)
		{
			for (int j = 0; j < nodes.size - i - 1; j++)
			{
				if (nodes[j].product.department_number.toLongLong() > nodes[j + 1].product.department_number.toLongLong())
				{
					temp = nodes[j];
					nodes[j] = nodes[j + 1];
					nodes[j + 1] = temp;
				}
			}
		}
	}

	int isEmpty() {
		if (nodes.size == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void searchByNumber(QString number, DoubleLinkedListOnArray& list) {
		DoubleLinkedListOnArray result;
		for (int i = 0; i < nodes.size; i++)
		{
			if (nodes[i].product.department_number == number)
			{
				result.add(nodes[i].product);
			}
		}
		list.nodes = result.nodes;
	}

	void searchByName(QString name, DoubleLinkedListOnArray& list) {
		DoubleLinkedListOnArray result;
		for (int i = 0; i < nodes.size; i++)
		{
			if (nodes[i].compairingSurnames(name))
			{
				result.add(nodes[i].product);
			}
		}
		list.nodes = result.nodes;
	}


	void deleteelementfromlist(QString Fullname, QString DepartmentNumber) {
		DoubleLinkedListOnArray result;
		for (int i = 0; i < nodes.size; i++)
		{
			if (nodes[i].product.fullname == Fullname && nodes[i].product.department_number == DepartmentNumber)
			{

			}
			else {
				result.nodes.push_back(nodes[i]);
			}
		}
		*this = result;
		
	}

	void save(DoubleLinkedListOnArray& list, QString filepath) {
		//output all data from list to a file with filepath filepath
		std::fstream file;
		if (!file.is_open())
		{
			file.open(filepath.toStdString(), std::ios::out | std::ios::trunc);
			file.clear();
			
			for (int i = 0; i < nodes.size; i++)
			{
				file << list.getProduct(i).fullname.toStdString() << std::endl;
				file << list.getProduct(i).department_number.toStdString() << std::endl;
				file << list.getProduct(i).position.toStdString() << std::endl;
				file << list.getProduct(i).date.toStdString() << std::endl;
				file << std::endl;
			}
			file.close();
		}
	}

	void ExperienceSort(QString date, DoubleLinkedListOnArray& list) {
		DoubleLinkedListOnArray result;
		for (int i = 0; i < nodes.size; i++)
		{
			if (DatesCompairing(nodes[i].product.date, date))
			{
				result.add(nodes[i].product);
			}
		}
		list.nodes = result.nodes;
	}

	int DatesCompairing(QString date, QString date2) {
		QString year1, year2, month1, month2, day1, day2;
		year1 = date.mid(0, 4);
		year2 = date2.mid(0, 4);
		month1 = date.mid(5, 2);
		month2 = date2.mid(5, 2);
		day1 = date.mid(8, 2);
		day2 = date2.mid(8, 2);
		if (year1 < year2 || (year1 == year2 && month1 < month2) || (year1 == year2 && month1 == month2 && day1 <= day2)) {
			return 1;
		}
		else {
			return 0;
		}
	}

};
#endif // DOUBLELIST_H
