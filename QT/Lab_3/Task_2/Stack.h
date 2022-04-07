#pragma once

class Stack {
public:
	char* data;
	int size;
	int top;
	
	Stack(int size = 100) {
		this->size = size;
		this->top = -1;
		this->data = new char[size];
	}
	
	~Stack() {
		delete[] data;
	}
	
	void push(int value) {
		if (top < size) {
			data[top++] = value;
		}
	}
	
	int pop() {
		if (top == 0) {
			return -1;
		}
		return data[--top];
	}
	
	int peek() {
		return data[top];
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
	
	char gettop() {
		return data[top];
	}
};
