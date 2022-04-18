#pragma once
#include <qstring.h>

class Node {
public:
	Node(QString data);
	~Node();
	QString getData();
	void setData(QString data);
	Node* getNext();
	void setNext(Node* next);
	
private:
	QString data;
	Node* next;	
};


class Queue {
public:
	Queue();
	~Queue();
	void enqueue(QString);
	std::string dequeue();
	QString peek();
	bool isEmpty();
	void clear();

private:
	Node* head;
	Node* tail;
	
};
