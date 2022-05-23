#include <iterator>
#include "ui_MainWindow.h"


//#include "MainWindow.h"

using namespace std;
template<typename T, typename data>
class ListNode {
public:

	std::pair<T, data> Data;
	ListNode<T, data>* next;
	ListNode<T, data>* previous;
	ListNode(T key, data value ) {
		Data = std::make_pair(key, value);
		next = NULL;
		previous = NULL;
	}
	/*Node<T>(Node<T>* n) {
		this->data = n->data;
		next = n->next;
		previous = n->previous;
	}*/
	~ListNode<T>() {

	}
	data getdata() {
		return Data.second;
	}
	ListNode<T, data>* getnext() {
		return next;
	}
	ListNode<T, data>* getprevious() {
		return previous;
	}
	void setnext(ListNode<T, data>* n) {
		next = n;
	}
	void setprevious(ListNode<T, data>* n) {
		previous = n;
	}
	//operator =
	ListNode<T, data>& operator=(ListNode<T, data>& n) {
		this->data = n.data;
		this->next = n.next;
		this->previous = n.previous;
		return *this;
	}

	/*Node<T>& operator=(Node<T>& n) {
		this->data = n.data;
		this->next = n.next;
		this->previous = n.previous;
	}*/
};

template<typename T, typename data>
class DoubleLinkedList {
private:
	ListNode<T, data>* head = nullptr;
	ListNode<T, data>* tail = nullptr;
	QString FilePath3 = "C:/Users/shchi/BSUIR/QT/Lab_3/servedlist.txt";
public:

	class ListIterator : public std::iterator<std::bidirectional_iterator_tag, ListNode<T, data>, ListNode<T, data>, ListNode<T, data>*, ListNode<T, data>&> {
	private:
		ListNode<T, data>* ptr;
	public:
		typedef 
			ListIterator(ListNode<T, data>* ptr = nullptr) : ptr(ptr) {};

		ListIterator(const ListIterator& other) : ptr(other.ptr) {};

		ListIterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		ListIterator operator++(int) {
			ListIterator temp(*this);
			ptr = ptr->next;
			return temp;
		}
		ListIterator& operator--() {
			ptr = ptr->previous;
			return *this;
		}
		ListIterator operator--(int) {
			ListIterator temp(*this);
			ptr = ptr->previous;
			return temp;
		}
		bool operator==(const ListIterator& other) {
			return ptr == other.ptr;
		}
		bool operator!=(const ListIterator& other) {
			return ptr != other.ptr;
		}
		ListNode<T, data>& operator*() {
			return *ptr;
		}
		ListNode<T, data>* operator->() {
			return ptr;
		}

	};

	ListIterator begin() {
		return ListIterator(head);
	}

	ListIterator end() {
		return ListIterator(tail ? tail->next : nullptr);
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
	int push_back(ListNode<T, data>* n) {
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

	ListNode<T, data>* getHead() {
		return head;
	}

	void setHead(ListNode<T, data>* n) {
		n->next = head->next;
		n->previous = nullptr;
		head->next->previous = n;		
		head = n;	
		head->data = n->data;
	}

	void sort() {
		ListNode<T, data>* current = head;
		ListNode<T, data>* next = head->next;
		while (next) {
			if (current->data.first > next->data.first) {
				ListNode<T, data>* temp = next->next;
				next->next = current;
				next->previous = current->previous;
				current->previous->next = next;
				current->previous = next;
				current = next;
				next = temp;
			}
			else {
				current = current->next;
				next = next->next;
			}
		}
	}

	void remove(ListNode<T, data>* n) {
		if (n == head) {
			head = head->next;
			head->previous = nullptr;
		}
		else if (n == tail) {
			tail = tail->previous;
			tail->next = nullptr;
		}
		else {
			n->previous->next = n->next;
			n->next->previous = n->previous;
		}
	}

	//inserting node at the beginning
	void insertAtBeginning(ListNode<T, data>* n) {
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
	void insertAtMiddle(ListNode<T, data>* n) {
		if (head == nullptr)
		{
			head = n;
			tail = n;
		}
		else {
			ListNode<T, data>* temp = head;
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
		ListNode<T, data>* temp = head;
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
	void pop_back() {
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
				ListNode<T, data>* temp = head;
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
		ListNode<T, data>* temp = head;
		while (temp != nullptr) {
			ListNode<T, data>* temp2 = temp->next;
			delete temp;
			temp = nullptr;
			temp = temp2;
		}
		head = nullptr;
		tail = nullptr;
	}

	void insert(QString data, QString newdata) {
		ListNode<T, data>* temp = head;
		ListNode<T, data>* newNode = new ListNode<T, data>(newdata);
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
			else if (temp == tail && temp->data == data) {
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
		ListNode<T, data>* temp = completelist.head;
		while (temp != nullptr) {
			this->push_back(temp);
			temp = temp->next;
		}
	}
};
