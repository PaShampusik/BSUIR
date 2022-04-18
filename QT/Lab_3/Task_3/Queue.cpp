#include "Queue.h"
#include <qstring.h>


Queue::Queue() {
	head = nullptr;
	tail = nullptr;
}

Queue::~Queue() {

}

void Queue::enqueue(QString num) {
	if (isEmpty()) {
		head = new Node(num);
		tail = head;
	}
	else {
		tail->setNext(new Node(num));
		tail = tail->getNext();
	}
}

void Queue::clear() {
	while (!(this->isEmpty()))
	{
		this->dequeue();
	}
}


	std::string Queue::dequeue() {
		if (isEmpty()) {
			return "";
		}
		else if (head->getNext() != nullptr) {
			std::string temp = head->getData().toStdString();
			Node* tempNode = head;
			head = head->getNext();
			head->setNext(tempNode->getNext()->getNext());
			tempNode->setNext(nullptr);
			delete tempNode;
			tempNode = nullptr;

			return temp;
		}
		else {
			std::string temp = head->getData().toStdString();
			delete head;
			head = nullptr;
			tail = nullptr;
			return temp;
		}
	}

	QString Queue::peek() {
		if (isEmpty()) {
			return "";
		}
		else {
			return head->getData();
		}
	}

	bool Queue::isEmpty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	Node::Node(QString data) : data(data), next(nullptr) {}

	Node::~Node() {
		delete next;
	}

	QString Node::getData() {
		return data;
	}

	void Node::setData(QString data) {
		this->data = data;
	}

	Node* Node::getNext() {
		return next;
	}

	void Node::setNext(Node * next) {
		this->next = next;
	}


