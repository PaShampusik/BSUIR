#include <iostream>
#include "MainWindow.h"

using namespace std;

class ControlBlock {

public:
	
	int key;
	Customer data;
	ControlBlock* next;
	ControlBlock* previous;

	ControlBlock(int k, int number = customers, QString fullname = "Mafioznik",
		QString address = "Winner street, house 3, flat 33", QString date = "01.01.0001") {
		key = k;
		data.number = number;
		data.fullname = fullname;
		data.address = address;
		data.date = date;
		++customers;
	}
};

class DoubleLinkedList {
public:
	ControlBlock* head;

	DoubleLinkedList() {
		head = NULL;
	}
	DoubleLinkedList(ControlBlock* n) {
		head = n;
	}

	//if CB exists
	ControlBlock* If_CB_Exists(int k) {
		ControlBlock* temp = NULL;
		ControlBlock* ptr = head;

		while (ptr != NULL)
		{
			if (ptr->key == k) {
				temp = ptr;
			}
			ptr = ptr->next;
		}
		return temp;
	}

	//append a CB to list

	void append(ControlBlock* n) {
		if (If_CB_Exists(n->key) != NULL)
		{
			//node already exxists.
		}
		else {
			if (head == NULL)
			{
				head = n;
				//node vecome a head
			}
			else {
				ControlBlock* ptr = head;
				while (ptr->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
				n->previous = ptr;
				//node appended
			}
		}
	}

	void preppend(ControlBlock* n) {
		if (If_CB_Exists(n->key) != NULL)
		{
			//node already exxists.
		}
		else {
			if (head == NULL)
			{
				head = n;
				//node become a head
			}
			else {
				head->previous = n;
				n->next = head;
				head = n;
				//node preppended
			}
		}
	}

	//inserting of node
	void insert(int k, ControlBlock* n) {
		ControlBlock* ptr = If_CB_Exists(k);

		if (ptr == NULL)
		{
			//no node with K number
		}
		else
		{
			if (If_CB_Exists(n->key) != NULL)
			{
				//node already here with key value
			}
			else
			{
				ControlBlock* nextnode = ptr->next;

				//inserting in the end
				if (nextnode == NULL)
				{
					ptr->next = n;
					n->previous = ptr;

				}

				//inserting in between
				else
				{
					n->next = nextnode;
					nextnode->previous = n;
					n->previous = ptr;
					ptr->next = n;

				}
			}
		}
	}

//deleting node by unique key

	void deletenode(int k) {
		if (head == NULL)
		{
			//no nodes
		}
		else if (head != NULL)
		{
			if (head->key == k)
			{
				head = head->next;

			}
			else 
			{
				ControlBlock* temp = NULL;
				ControlBlock* prevptr = NULL;
				ControlBlock* currentptr = head->next;
				while (currentptr->key!=NULL)
				{
					if (currentptr->key == k)
					{
						temp = currentptr;
						currentptr = NULL;
					}
					else
					{
						prevptr = prevptr->next;
						currentptr = currentptr->next;
					}
				}
				if (temp != NULL)
				{
					prevptr->next = temp->next;
				}
				else
				{
					//no node with such key
				}
			}
		}
	}

	//update node number by key
	void updatenodenumber(int k, int number){
		ControlBlock* ptr = If_CB_Exists(k);
		if (ptr != NULL)
		{
			ptr->data.number = number;
		}
		else
		{
			//node with such key
		}
	}

	//update node Fullname by key
	void updatenodenumber(int k, QString fullname) {
		ControlBlock* ptr = If_CB_Exists(k);
		if (ptr != NULL)
		{
			ptr->data.fullname = fullname;
		}
		else
		{
			//node with such key
		}
	}


	//list print
	void printlist(QTableWidget* tabewidget){
		if (head == NULL)
		{
			//no nodes in list
		}
		else
		{
			ControlBlock* temp = head;
			while (temp != NULL) {

				


				temp = temp->next;
			}
		}
};


