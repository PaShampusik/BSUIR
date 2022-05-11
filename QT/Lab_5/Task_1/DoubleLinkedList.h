#include <iterator>
#include "ui_MainWindow.h"


//#include "MainWindow.h"

using namespace std;
template<typename T>
class Node {
public:

	T data;
	Node<T>* next;
	Node<T>* previous;
	Node<T>(T data) {
		this->data = data;
		next = nullptr;
		previous = nullptr;
	}
	/*Node<T>(Node<T>* n) {
		this->data = n->data;
		next = n->next;
		previous = n->previous;
	}*/
	~Node<T>() {

	}
	T getdata() {
		return data;
	}
	Node<T>* getnext() {
		return next;
	}
	Node<T>* getprevious() {
		return previous;
	}
	void setnext(Node<T>* n) {
		next = n;
	}
	void setprevious(Node<T>* n) {
		previous = n;
	}
	Node<T>& operator=(Node<T>& n) {
		this->data = n.data;
		this->next = n.next;
		this->previous = n.previous;
	}
};

template<typename T>
class DoubleLinkedList {
private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	QString FilePath3 = "C:/Users/shchi/BSUIR/QT/Lab_3/servedlist.txt";
public:

	class Iterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>, Node<T>, Node<T>*, Node<T>&> {
	private:
		Node<T>* ptr;
	public:
		Iterator(Node<T>* ptr = nullptr) : ptr(ptr) {};

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
		Node<T>& operator*() {
			return *ptr;
		}
		Node<T>* operator->() {
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
	int insertAtEnd(Node<T>* n) {
		/*if (head)
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
		}*/
		if (isEmpty()) {
			head = n;
			tail = n;
			head->next = nullptr;
			head->previous = nullptr;
			tail->next = nullptr;
			tail->previous = nullptr;
			return 0;
		}
		else {
			tail->next = n;
			n->previous = tail;
			n->next = nullptr;
			tail = n;
			return 0;
		}
	}

	Node<T>* getHead() {
		return head;
	}

	//inserting node at the beginning
	void insertAtBeginning(Node<T>* n) {
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
	void insertAtMiddle(Node<T>* n) {
		if (head == nullptr)
		{
			head = n;
			tail = n;
		}
		else {
			Node<T>* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = n;
			n->previous = temp;
			tail = n;
		}
	}

	void deleteNode(T data) {
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == data)
			{
				if (temp == head)
				{
					head = temp->next;
					head->previous = nullptr;
					break;
				}
				else if (temp != tail && temp != head)
				{
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					//delete temp;
					temp = nullptr;
					break;
				}
				else
				{
					tail = temp->previous;
					//delete temp;
					temp = nullptr;
					break;

				}
			}
			else
			{
				temp = temp->next;
			}
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
				delete head;
				head = nullptr;
				delete tail;
				tail = nullptr;
			}
			else {
				Node<T>* temp = head;
				while (temp->next != tail)
				{
					temp = temp->next;
				}
				tail = temp;
				delete tail->next;
				tail->next = nullptr;
			}
		}

	}

	void clear() {
		Node<T>* temp = head;
		while (temp != nullptr) {
			Node<T>* temp2 = temp->next;
			delete temp;
			temp = nullptr;
			temp = temp2;
		}
		head = nullptr;
		tail = nullptr;
	}

	void insert(QString data, QString newdata) {
		Node<T>* temp = head;
		Node<T>* newNode = new Node<T>(newdata);
		while (temp != nullptr) {
			if (temp == head && temp->data == data)
			{
				head->previous = newNode;
				newNode->next = head;
				newNode->previous = nullptr;
				head = newNode;
				break;
			}
			else if (temp->getnext()->data == data && temp != tail) {
				newNode->next = temp->next;
				temp->next = newNode;
				newNode->previous = temp;
				newNode->next->previous = newNode;
				break;
			}
			else if(temp == tail && temp->data == data) {
				tail->previous->next = newNode;
				newNode->previous = tail->previous;
				newNode->next = tail;
				tail->previous = newNode;
				break;
			}
			temp = temp->next;
		}
	}

	void copy(DoubleLinkedList& completelist) {
		Node<T>* temp = completelist.head;
		while (temp != nullptr) {
			this->insertAtEnd(temp);
			temp = temp->next;
		}
	}
};

