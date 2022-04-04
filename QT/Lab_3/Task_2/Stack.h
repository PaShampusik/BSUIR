#pragma once
template<class T>
class Stack {
public:
	Stack() {
		top = 0;
	}
	~Stack() {
		delete[] stack;
	}


	void push(T) {
		if (top == maxSize) {
			cout << "Stack is full" << endl;
			return;
		}
		top++;
		arr[top] = item;
	}

	T pop() {
		if (top == NULL) {
			return NULL;
		}
		T temp = top->data;
		top = top->next;
		return temp;
	}

	T peek() {
		return stack[top];
	}


	bool isEmpty() {
		return top == 0;
	}
	
private:
	int top;
	int maxSize;
	T* stack;
};