#include <iterator>
#include "ui_MainWindow.h"


//#include "MainWindow.h"

using namespace std;

class Node {
public:

	Customer* data;
	Node* next;
	Node* previous;
	Node(Customer* data) {
		this->data = data;
		next = nullptr;
		previous = nullptr;
	}
	Customer* getdata() {
		return data;
	}
	Node* getnext() {
		return next;
	}
	Node* getprevious() {
		return previous;
	}
	void setnext(Node* n) {
		next = n;
	}
	void setprevious(Node* n) {
		previous = n;
	}
	bool compairingSurnames(QString name) {
		bool k = 1;
		int i = 0;
		while (data->fullname.toStdString()[i] != ' ' && i < min(data->fullname.length(), name.length())) {
			if (data->fullname.toStdString()[i] == name.toStdString()[i]) {}
			else
			{
				k = 0;
			}
			++i;
		}
		return k;
	}
};

class DoubleLinkedList {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	QString FilePath3 = "C:/Users/shchi/BSUIR/QT/Lab_3/servedlist.txt";
public:

	class Iterator : public std::iterator<std::bidirectional_iterator_tag, Node, Node, Node*, Node&> {
	private:
		pointer ptr;
	public:
		Iterator(pointer ptr = nullptr) : ptr(ptr) {};

		Iterator(const Iterator& other) : ptr(other.ptr) {};

		Iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp(*this);
			ptr = ptr->next;
			return temp;
		}
		Iterator& operator--() {
			ptr = ptr->previous;
			return *this;
		}
		Iterator operator--(int) {
			Iterator temp(*this);
			ptr = ptr->previous;
			return temp;
		}
		bool operator==(const Iterator& other) {
			return ptr == other.ptr;
		}
		bool operator!=(const Iterator& other) {
			return ptr != other.ptr;
		}
		reference operator*() {
			return *ptr;
		}
		pointer operator->() {
			return ptr;
		}

	};

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(tail ? tail->next : nullptr);
	}

	DoubleLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	//if list is empty
	bool isEmpty() {
		return head == nullptr;
	}

	//inserting node at the end
	int insertAtEnd(Node* n) {
		if (n->data->number == "" && n->data->date == "" && n->data->address == "" && n->data->fullname == "")
		{
			return 1;
		}
		else {

			Node* element = new Node(*n);
			if (head)
			{
				tail->next = element;
				element->previous = tail;
				element->next = nullptr;
				tail = element;
				return 0;
			}
			else {
				head = element;
				head->next = nullptr;
				head->previous = nullptr;
				tail = head;
				return 0;
			}
		}
	}

	//inserting node at the beginning
	void insertAtBeginning(Node* n) {
		if (head == nullptr)
		{
			head = n;
			tail = n;
		}
		else {
			head->previous = n;
			n->next = head;
			head = n;
		}
	}

	//inserting node at the middle
	void insertAtMiddle(Node* n) {
		if (head == nullptr)
		{
			head = n;
			tail = n;
		}
		else {
			Node* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = n;
			n->previous = temp;
			tail = n;
		}
	}


	//deleting node from the end
	void deleteFromEnd() {
		if (head == nullptr)
		{
			//no nodes
		}
		else if (head != nullptr)
		{
			if (head == tail)
			{
				head = nullptr;
				tail = nullptr;
			}
			else {
				Node* temp = head;
				while (temp->next != tail)
				{
					temp = temp->next;
				}
				tail = temp;
				tail->next = nullptr;
			}
		}
	}

	void sort() {
		//deleting dublicates of nodes with the same name and address
		Node* temp = head;
		while (temp != nullptr) {
			Node* temp2 = temp->next;
			while (temp2 != nullptr) {
				if (temp->data->getname() == temp2->data->getname() || temp->data->getaddress() == temp2->data->getaddress()) {

					//Node* temp3 = temp2->next;
					if (temp2 == head && temp2 != tail)
					{
						head = temp2->next;
						head->previous = nullptr;
						delete temp2;
						temp2 = nullptr;
					}
					else if (temp2 == tail && temp2 != head) {
						tail = temp2->previous;
						tail->next = nullptr;
						delete temp2;
						temp2 = nullptr;
					}
					else if (temp2 == tail && temp2 == head) {
						head = nullptr;
						tail = nullptr;
						delete temp2;
						temp2 = nullptr;
					}
					else {
						temp2->previous->next = temp2->next;
						temp2->next->previous = temp2->previous;
						delete temp2;
						temp2 = nullptr;
					}


					/*temp2->previous->next = temp2->next;
					temp2->next->previous = temp2->previous;
					delete temp2;*/
				}
				else {
					temp2 = temp2->next;
				}
			}
			temp = temp->next;
		}
	}

	DoubleLinkedList& searchByNumber(QString number) {
		Node* temp = this->head;
		DoubleLinkedList Temp;

		//deletes all nodes with the different number
		while (temp != nullptr) {

			Node* temp2 = temp->next;

			if (temp->data->getnumber() != number) {
				/*if (temp == list.head && temp != list.tail)
				{
					list.head = temp->next;
					list.head->previous = nullptr;
					delete temp;
					temp = nullptr;
				}
				else if (temp == list.tail && temp != list.head) {
					list.tail = temp->previous;
					list.tail->next = nullptr;
					delete temp;
					temp = nullptr;
				}
				else if (temp == list.tail && temp == list.head) {
					list.head = nullptr;
					list.tail = nullptr;
					delete temp;
					temp = nullptr;
				}
				else {
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
					temp = nullptr;
				}*/
			}
			else {
				Temp.insertAtEnd(temp);
			}
			temp = temp2;
		}
		return Temp;
	}


	DoubleLinkedList& searchByDate(QString date) {
		Node* temp = head;
		DoubleLinkedList Temp;

		//deletes all nodes with the different name
		while (temp != nullptr) {

			Node* temp2 = temp->next;

			if (temp->data->getdate() != date) {
				/*if (temp == head && temp != tail)
				{
					head = temp->next;
					head->previous = nullptr;
					delete temp;
				}
				else if (temp == tail && temp != head) {
					tail = temp->previous;
					tail->next = nullptr;
					delete temp;
				}
				else if (temp == tail && temp == head) {
					head = nullptr;
					tail = nullptr;
					delete temp;
				}
				else {
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
				}*/
			}
			else {
				DoubleLinkedList Temp;
				Temp.insertAtEnd(temp);
				return Temp;
			}
			temp = temp2;
		}
		return Temp;

	}


	DoubleLinkedList& searchByName(QString name) {
		Node* temp = head;
		DoubleLinkedList Temp;

		//deletes all nodes with the different name
		while (temp != nullptr) {

			Node* temp2 = temp->next;

			if (!(temp->compairingSurnames(name))) {
				/*if (temp == head && temp != tail)
				{
					head = temp->next;
					delete temp;
				}
				else if (temp == tail && temp != head) {
					tail = temp->previous;
					tail->next = nullptr;
					delete temp;
				}
				else if (temp == tail && temp == head) {
					head = nullptr;
					tail = nullptr;
					delete temp;
				}
				else {
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
				}*/
			}
			else {
				Temp.insertAtEnd(temp);
			}

			temp = temp2;
		}
		return Temp;
	}

	void clear() {
		Node* temp = head;
		while (temp != nullptr) {
			Node* temp2 = temp->next;
			delete temp;
			temp = nullptr;
			temp = temp2;
		}
		head = nullptr;
		tail = nullptr;
	}

	void copy(DoubleLinkedList& completelist) {
		Node* temp = completelist.head;
		while (temp != nullptr) {
			this->insertAtEnd(temp);
			temp = temp->next;
		}
	}

	void save(DoubleLinkedList& list, QString filepath) {
		//output all data from list to a file with filepath filepath
		std::fstream file;
		if (!file.is_open())
		{
			file.open(filepath.toStdString(), ios::out | ios::trunc);
			file.clear();



			Node* temp = list.head;
			while (temp)
			{
				file << temp->data->number.toStdString() << std::endl;

				file << temp->data->fullname.toStdString() << std::endl;
				file << temp->data->address.toStdString() << std::endl;
				file << temp->data->date.toStdString() << std::endl;
				file << std::endl;
				temp = temp->next;
			}

			file.close();

		}
		
	}

	void deleteelementfromlist(QString name, QString number) {
		//deleting dublicates of nodes with the same name and address
		Node* temp = head;
		if (name == "" || number == "")
		{

		}
		while (temp != nullptr) {
			if (temp->data->getname() == name && temp->data->getnumber() == number) {
				Node* temp2 = temp->next;
				if (temp == head && temp != tail)
				{
					head = temp->next;
					head->previous = nullptr;
					delete temp;
					temp = nullptr;
				}
				else if (temp == tail && temp != head) {
					tail = temp->previous;
					tail->next = nullptr;
					delete temp;
					temp = nullptr;
				}
				else if (temp == tail && temp == head) {
					head = nullptr;
					tail = nullptr;
					delete temp;
					temp = nullptr;
				}
				else {
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
					temp = nullptr;
				}
				temp = temp2;
			}
			else {
				temp = temp->next;
			}
		}
	}
};

