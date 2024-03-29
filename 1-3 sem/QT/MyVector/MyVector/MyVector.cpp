﻿// MyVector.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "MyVector.h"

template <typename T>
MyVector<T>::MyVector() {
	data = nullptr;
	size = 0;
	capacity = 0;
}
template <typename T>
MyVector<T>::MyVector(int size) {
	data = new T[size];
	this->size = size;
	capacity = size;
}
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) {
	data = new T[other.capacity];
	size = other.size;
	capacity = other.capacity;
	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}
template <typename T>
MyVector<T>::~vector() {
	delete[] data;
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
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
template <typename T>
T& MyVector<T>::operator[](int index) {
	return data[index];
}
template <typename T>
const T& MyVector<T>::operator[](int index) const {
	return data[index];
}
template <typename T>
T& MyVector<T>::operator=(T value) {
	for (int i = 0; i < size; i++)
		data[i] = value;
	return *this;
}
template <typename T>
int MyVector<T>::getSize() const {
	return size;
}
template <typename T>
void MyVector<T>::push_back(const T& value) {

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
template <typename T>
void MyVector<T>::pop_back() {
	T* temp = new T[capacity];
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = data[i];
	}
	size--;
	delete[] data;
	data = temp;
}
template <typename T>
void MyVector<T>::insert(int index, const T& value) {
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
template <typename T>
void MyVector<T>::erase(int index) {
	for (int i = index; i < size - 1; i++)
		data[i] = data[i + 1];
	size--;
}
template <typename T>
void MyVector<T>::clear() {
	size = 0;
}
template <typename T>
void MyVector<T>::reserve(int newCapacity) {
	if (newCapacity > capacity) {
		capacity = newCapacity;
		T* temp = new T[capacity];
		for (int i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}
}
template <typename T>
void MyVector<T>::resize(int newSize) {
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
template <typename T>
void MyVector<T>::shrink_to_fit() {
	capacity = size;
	T* temp = new T[capacity];
	for (int i = 0; i < size; i++)
		temp[i] = data[i];
	delete[] data;
	data = temp;
}
template <typename T>
void MyVector<T>::swap(MyVector<T>& other) {
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