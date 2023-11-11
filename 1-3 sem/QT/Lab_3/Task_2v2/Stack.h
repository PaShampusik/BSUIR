
#pragma once
#include <tuple>


class Stack {
public:
	std::tuple<int, int, char>* data;
	int size;
	int top;

	Stack(int size = 30) : size(size), top(-1) {
		this->data = new std::tuple<int, int, char>[size];
		/*for (int i = 0; i < size; i++)
		{
			this->data[i] = 0;
		}*/
	}

	~Stack() {
		delete[] data;
		data = nullptr;
		top = -1;
		size = 0;
	}

	void push(int line, int column, char value) {
		if (top < size) {
			data[++top] = { line , column, value };
		}
	}

	std::tuple<int, int, char> pop() {
		if (top == -1) {
			return { 0, 0, '\0' };
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

	char gettop() {
		return std::get<2>(data[top]);
	}

	int gettopline() {
		return std::get<0>(data[top]);
	}

	int gettopcolumn() {
		return std::get<1>(data[top]);
	}

	void clear() {
		top = -1;
	}

};
#pragma once
