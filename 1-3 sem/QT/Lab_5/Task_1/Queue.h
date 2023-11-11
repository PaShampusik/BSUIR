#pragma once

#include <qstring.h>



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
	class NodeQ {
	public:
		NodeQ(QString data);
		~NodeQ();
		QString getData();
		void setData(QString data);
		NodeQ* getNext();
		void setNext(NodeQ* next);

	private:
		QString data;
		NodeQ* next;
	};
	NodeQ* head;
	NodeQ* tail;

};
