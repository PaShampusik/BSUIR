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
		head = new NodeQ(num);
		tail = head;
	}
	else {
		tail->setNext(new NodeQ(num));
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
		NodeQ* tempNode = head;
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

Queue::NodeQ::NodeQ(QString data) : data(data), next(nullptr) {}

Queue::NodeQ::~NodeQ() {
	delete next;
}

QString Queue::NodeQ::getData() {
	return data;
}

void Queue::NodeQ::setData(QString data) {
	this->data = data;
}


Queue::NodeQ* Queue::NodeQ::getNext() {
	return next;
}

void Queue::NodeQ::setNext(NodeQ* next) {
	this->next = next;
}



