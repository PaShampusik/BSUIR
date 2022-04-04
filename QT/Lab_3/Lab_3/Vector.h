#pragma once

#include <iostream>
#include <vector>

template <typename T>
class vector {
private:
	T* arr;
	size_t size;
	size_t capacity;

public:
	
	size_t size() const {
		return size;
	}

	void resize(size_t newsize) {
		if (newsize > capacity) {
			capacity = newsize;
			T* newarr = new T[capacity];
			for (size_t i = 0; i < size; i++) {
				newarr[i] = arr[i];
			}
			delete[] arr;
			arr = newarr;
		}
		size = newsize;
	}
	size_t capacity()const {
		return capacity;
	}

	void reserve(size_t newcap) {
		if (newcap <= cap) return;
		T* newarr = reinterpret_cast<T*>(new uint8_t[newcap * sizeof(T)]);
		for (size_t i = 0; i < size; ++i)
		{
			try {
				new(newarr + i) T(arr[i]);//todo avoid of copy????????????
			}
			catch (...) {
				for (size_t  j = 0; j < i; ++j )
				{
					(newarr + j)->T();
				}
				delete[] reinterpret_cast<uint8_t*>(newarr);
				throw;
			}
		}
		for (size_t i = 0; i < size; ++i)
		{
			(arr + i) -> ~T();
		}

		delete[] reinterpret_cast<uint8_t*>(arr);
		cap = newcap;
		arr = newarr;
	}

	void push_back(const T& value) {
		if (size == capacity) {
			reserve(capacity * 2);
		}
		new(arr + size) T(value);
		size++;
		
	}

	void pop_back() {
		if (size == 0) return;
		(arr + size - 1)->~T();
		--size;
	}
};