#pragma once

#include<iostream>

template<class T>
class MyVector {

public:
	struct random_access_iterator {
		T* ptr;
		random_access_iterator(const random_access_iterator&) {
			
		}
		random_access_iterator(T* ptr) : ptr(ptr){};
		~random_access_iterator() {}
		random_access_iterator& operator=(const random_access_iterator& other) {
			ptr = other.ptr;
			return *this;
		}
		T& operator*(){
			return *ptr;
		}
		void swap(random_access_iterator& lhs, random_access_iterator& rhs) {
			T* temp = lhs.ptr;
			lhs.ptr = rhs.ptr;
			rhs.ptr = temp;
		}
		random_access_iterator& operator--() {
			--ptr;
			return *this;
		}
		random_access_iterator operator--(int) {
			random_access_iterator temp = *this;
			--ptr;
			return temp;
		}
		const T& operator*() const;
		random_access_iterator operator++(int) {
			random_access_iterator temp = *this;
			++ptr;
			return temp;
		}
		random_access_iterator& operator++() {
			++ptr;
			return *this;
		}
		T* operator->() const {
			return ptr;
		}
		bool operator==(const random_access_iterator& second) {
			return ptr == second.ptr;
		}
		bool operator!=(const random_access_iterator& other) {
			return ptr != other.ptr;
		}
		bool operator<(const random_access_iterator& second) {
			return ptr < second.ptr;
		}
		bool operator>(const random_access_iterator& second) {
			return ptr > second.ptr;
		}
		bool operator<=(const random_access_iterator& second) {
			return ptr <= second.ptr;
		}
		bool operator>=(const random_access_iterator& second) {
			return ptr >= second.ptr;
		}
	};


	T* data;
	int size;
	int capacity;
	MyVector();
	MyVector(int size);
	MyVector(const MyVector<T>& other);
	~MyVector();
	MyVector<T>& operator=(const MyVector<T>& other);
	const T& operator[](int index) const;
	T& operator[](int index);
	T& operator=(T value);
	T* operator++() {
		++data;
		return data;
	}
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
	void assign(int count, const T& value);
	T& at(int index);
	T& back();
	inline random_access_iterator begin();
	int get_capacity();
	inline const random_access_iterator cbegin() const;
	inline const random_access_iterator cend() const;
	//riterator crbegin();
	//riterator crend();
	T* get_data();
	void emplace(int index, const T& value);
	void emplace_back(const T& value);
	bool empty();
	inline random_access_iterator end();
	T& front();
	int max_size();
	//riterator rbegin();
	//riterator rend();
};
