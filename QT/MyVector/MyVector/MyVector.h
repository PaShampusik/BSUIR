#pragma once

template<class T>
class MyVector {

public:
	T* data;
	int size;
	int capacity;
	MyVector();
	MyVector(int size);
	MyVector(const MyVector<T>& other);
	~MyVector();
	MyVector<T>& operator=(const MyVector<T>& other);	
	T& operator[](int index);
	T& operator=(T value);
	int getSize() const;
	void push_back(const T& value);
	void pop_back();
	void insert(int index, const T& value);
	void erase(int index);
	void clear();
	void reserve(int newCapacity);
	void resize(int newSize);	
	void shrink_to_fit();
	void swap(MyVector<T>& other);
};
