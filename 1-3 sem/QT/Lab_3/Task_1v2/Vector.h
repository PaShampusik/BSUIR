#pragma once

template<class T>
class vector {

public:
	T* data;
	int size;
	int capacity;
	vector(){
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	vector(int size){
		data = new T[size];
		this->size = size;
		capacity = size;
	}
	vector(const vector<T>& other){
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;
		for (int i = 0; i < size; i++)
			data[i] = other.data[i];
	}
	~vector(){
		delete[] data;
	}
	vector<T>& operator=(const vector<T>& other){
		if (this != &other){
			delete[] data;
			data = new T[other.capacity];
			size = other.size;
			capacity = other.capacity;
			for (int i = 0; i < size; i++)
				data[i] = other.data[i];
		}
		return *this;
	}
	T& operator[](int index){
		return data[index];
	}
	const T& operator[](int index) const{
		return data[index];
	}
	T& operator=(T value){
		for (int i = 0; i < size; i++)
			data[i] = value;
		return *this;
	}
	int getSize() const{
		return size;
	}
	void push_back(const T& value){
		
		if (size == capacity){
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
	void pop_back(){
		T* temp = new T[capacity];
		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = data[i];
		}
		size--;
		delete[] data;
		data = temp;
	}
	void insert(int index, const T& value){
		if (size == capacity){
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
		
	void erase(int index){
		for (int i = index; i < size - 1; i++)
			data[i] = data[i + 1];
		size--;
	}
	void clear(){
		size = 0;
	}
	void reserve(int newCapacity){
		if (newCapacity > capacity){
			capacity = newCapacity;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
	}
	void resize(int newSize){
		if (newSize > capacity){
			capacity = newSize;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
		size = newSize;
	}
	/*void resize(int newSize, const T& value){
		if (newSize > capacity){
			capacity = newSize;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
		for (int i = size; i < newSize; i++)
			data[i] = value;
		size = newSize;
	}*/
	void shrink_to_fit(){
		capacity = size;
		T* temp = new T[capacity];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}
	void swap(vector<T>& other){
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
};