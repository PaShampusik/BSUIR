#pragma once

class Stack {
public:
	QString* data;
	int size;
	int top;

	Stack(int size = 30) : size(size), top(-1) {
		this->data = new QString[30];
	}

	~Stack() {
		delete[] data;
		data = nullptr;
		top = 0;
		size = 0;
	}

	void push(QString value) {
		if (top < size) {
			data[++top] = { value };
		}
	}

	QString pop() {
		if (top == -1) {
			return 0;
		}
		return data[top--];
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top == size;
	}

	int getSize() {
		return size;
	}

	QString gettop() {
		return data[top];
	}

	void clear() {
		top = -1;
	}

};
