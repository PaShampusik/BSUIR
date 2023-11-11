#pragma once

#include <tuple>

class Stack {
public:
	char* data;
	int size;
	int top;

	Stack(int size = 100) : size(size), top(-1) {
		this->data = new char[size];
	}

	~Stack() {
		delete[] data;
		data = nullptr;
		top = -1;
		size = 0;
	}

	void push(char value) {
		if (top < size) {
			data[++top] = value;
		}
	}

	char pop() {
		if (top == -1) {
			return ' ';
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
		return top;
	}

	char gettop() {
		return data[top];
	}

	void clear() {
		top = -1;
	}

};