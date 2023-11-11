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

	struct reverse_iterator {
		T* ptr;
		reverse_iterator(const reverse_iterator&) {

		}
		reverse_iterator(T* ptr) : ptr(ptr) {};
		~reverse_iterator() {}
		reverse_iterator& operator=(const reverse_iterator& other) {
			ptr = other.ptr;
			return *this;
		}
		T& operator*() {
			return *ptr;
		}
		void swap(reverse_iterator& lhs, reverse_iterator& rhs) {
			T* temp = lhs.ptr;
			lhs.ptr = rhs.ptr;
			rhs.ptr = temp;
		}
		reverse_iterator& operator--() {
			--ptr;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp = *this;
			--ptr;
			return temp;
		}
		const T& operator*() const;
		reverse_iterator operator++(int) {
			reverse_iterator temp = *this;
			++ptr;
			return temp;
		}
		reverse_iterator& operator++() {
			++ptr;
			return *this;
		}
		T* operator->() const {
			return ptr;
		}
		bool operator==(const reverse_iterator& second) {
			return ptr == second.ptr;
		}
		bool operator!=(const reverse_iterator& other) {
			return ptr != other.ptr;
		}
		bool operator<(const reverse_iterator& second) {
			return ptr < second.ptr;
		}
		bool operator>(const reverse_iterator& second) {
			return ptr > second.ptr;
		}
		bool operator<=(const reverse_iterator& second) {
			return ptr <= second.ptr;
		}
		bool operator>=(const reverse_iterator& second) {
			return ptr >= second.ptr;
		}
	};


	T* data;
	int size;
	int capacity;
	MyVector() {		
		size = 0;
		capacity = 2;
		data = new T[capacity];
	}
	MyVector(int size) {
		data = new T[size];
		this->size = size;
		capacity = size;
	}
	MyVector(const MyVector<T>& other) {
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;
		for (int i = 0; i < size; i++)
			data[i] = other.data[i];
	}
	~MyVector() {
		delete[] data;
	}
	MyVector<T>& operator=(const MyVector<T>& other) {
		if (this != &other) {
			delete[] data;
			data = new T[other.capacity];
			size = other.size;
			capacity = other.capacity;
			for (int i = 0; i < size; i++)
				data[i] = other.data[i];
		}
		return *this;
	}
	T& operator=(T value) {
		for (int i = 0; i < size; i++)
			data[i] = value;
		return *this;
	}
	T& operator[](int index) {
		return data[index];
	}	
	const T& operator[](int index) const {
		return data[index];
	}
	
	T* operator++() {
		++data;
		return data;
	}
	int getSize() const {
		return size;
	}
	void push_back(const T& value) {
		if (size == capacity) {
			T* temp = new T[capacity * 2];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
			capacity *= 2;
		}
		if (size == 0)
		{
			capacity = 2;
			data = new T[capacity];
		}
		data[size] = value;
		size++;
	}
	void pop_back() {
		T* temp = new T[capacity];
		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = data[i];
		}
		size--;
		delete[] data;
		data = temp;
	}
	void insert(int index, const T& value) {
		if (size == capacity) {
			capacity *= 2;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
		for (int i = size; i > index; i--)
			data[i] = data[i - 1];
		data[index] = value;
		size++;
	}
	void erase(int index) {
		for (int i = index; i < size - 1; i++)
			data[i] = data[i + 1];
		size--;
	}
	void clear() {
		size = 0;
	}
	void reserve(int newCapacity) {
		if (newCapacity > capacity) {
			capacity = newCapacity;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
	}
	void resize(int newSize) {
		if (newSize > capacity) {
			capacity = newSize;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
		size = newSize;
	}
	void shrink_to_fit() {
		capacity = size;
		T* temp = new T[capacity];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}
	void swap(MyVector<T>& other) {
		T* temp = data;
		data = other.data;
		other.data = temp;
		int tempSize = size;
		size = other.size;
		other.size = tempSize;
		int tempCapacity = capacity;
		capacity = other.capacity;
		other.capacity = tempCapacity;
	}
	void assign(int count, const T& value) {
		if (count > capacity) {
			capacity = count;
			T* temp = new T[capacity];
		}
	}
	T& at(int index) {
		if (index < 0 || index >= size)
			throw std::out_of_range("Index out of range");
		return data[index];
	}
	T& back() {
		if (size == 0)
			throw std::out_of_range("Index out of range");
		return data[size - 1];
	}
	int get_capacity() {
		return capacity;
	}
	T* get_data() {
		return data;
	}
	void emplace(int index, const T& value) {
		if (size == capacity) {
			capacity *= 2;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
		for (int i = size; i > index; i--)
			data[i] = data[i - 1];
		data[index] = value;
		size++;
	}
	void emplace_back(const T& value) {
		if (size == capacity) {
			T* temp = new T[capacity * 2];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
			capacity *= 2;
		}
		if (size == 0)
		{
			capacity = 2;
			data = new T[capacity];
		}
		data[size] = value;
		size++;
	}
	T& front() {
		if (size == 0)
			throw std::out_of_range("Vector is empty");
		return data[0];
	}
	bool empty() {
		return size == 0;
	}
	int max_size() {
		return capacity;
	}
	inline random_access_iterator end() {
		if (size == 0) {
			return begin();
		}
		return MyVector<T>::random_access_iterator(std::addressof(data[size]));
	}
	inline random_access_iterator begin() {
		return MyVector<T>::random_access_iterator(std::addressof(data[0]));
	}
	inline const random_access_iterator cbegin() const {
		return MyVector<T>::random_access_iterator(std::addressof(data[0]));
	}
	inline const random_access_iterator cend() const {
		if (size == 0) {
			return cbegin();
		}
		return MyVector<T>::random_access_iterator(std::addressof(data[size]));
	}
	inline const reverse_iterator crend() {
		return MyVector<T>::random_access_iterator(std::addressof(data[0]));
	}
	inline const reverse_iterator crbegin() const{
		if (size == 0)
		{
			return crend();
		}
		return MyVector<T>::random_access_iterator(std::addressof(data[size - 1]));
	}
	inline reverse_iterator rbegin() {
		if (size == 0)
		{
			return crend();
		}
		return MyVector<T>::random_access_iterator(std::addressof(data[size - 1]));
	}
	inline reverse_iterator rend() {
		return MyVector<T>::random_access_iterator(std::addressof(data[0]));
	}
};
