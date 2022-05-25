#pragma once
#include <functional>
#include<forward_list>
#include<list>


template<typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class HashTable {
private:
	int size = 10;
	int count;
	int hash(Key key) {
		return Hash()(key) % size;
	}
public:
	
    std::forward_list<std::pair<const Key, T>>* table;
	std::list<std::pair<const Key, T>> iteratorlist;
	
	T& operator[](const Key& key) {
		int index = hash(key);
		for (auto& i : table[index]) {
			if (KeyEqual()(i.first, key)) {
				return i.second;
			}
		}
		table[index].push_front(std::make_pair(key, T()));
		count++;
		return table[index].front().second;
	}
	
	T operator[](const Key& key) const {
		int index = hash(key);
		for (auto& i : table[index]) {
			if (KeyEqual()(i.first, key)) {
				return i.second;
			}
		}
		return T();
	}
	
	HashTable() {
		this->size = size;
		count = 0;
		table = new std::forward_list<std::pair<const Key, T>>[size];
	}
	~HashTable() {
		delete[] table;
	}
	
	void insert(Key key, T data) {
		if ((double)(count / size) > 0.8)
		{
			rehash();
		}
		int index = hash(key);
		table[index].push_front(std::pair<const Key, T>(key, data));
		iteratorlist.push_front(std::pair<const Key, T>(key, data));
		count++;
	}
	
	bool find(Key key, T data) {
		auto& bucket = table[hash(key)];
		for (auto& i : bucket)
		{
			if (i.second == data)
			{
				return true;
			}
		}
		return false;
	}

	void remove(Key key, T data) {
		int index = hash(key);
		table[index].remove(std::pair<const Key, T>(key, data));
		iteratorlist.remove(std::pair<const Key, T>(key, data));
	}

	/*int FindMin() {
		int min = 1000, ind = -1;     
		for (int i = 0; i < size; i++)
		{
			Node<std::pair<const Key, T>>* temp = table[i].getHead();
			while (temp != nullptr) {
				if (temp->data.second < min) {
					min = temp->data.second;
					ind = i;
				}c
				temp = temp->next;
			}
		}
		return ind + 1;
	}*/

	int getsize() {
		return size;
	}
	void rehash() {
		int oldsize = size;
		size = size * 2;
		std::forward_list<std::pair<const Key, T>>* oldtable = table;
		table = new std::forward_list<std::pair<const Key, T>>[size];
		for (int i = 0; i < oldsize; i++)
		{
			auto& bucket = oldtable[i];
			for (auto& i : bucket)
			{
				int index = hash(i.first);
				table[index].push_front(i);
			}
		}
		delete[] oldtable;
	}

	void clear() {
		for (int i = 0; i < size; i++)
		{
			table[i].clear();
		}
	}
	
	typename std::list<std::pair<const Key, T>>::iterator begin() {
		return iteratorlist.begin();
	}

	typename std::list<std::pair<const Key, T>>::iterator end() {
		return iteratorlist.end();
	}

	typename std::list<std::pair<const Key, T>>::const_iterator cbegin() {
		return iteratorlist.cbegin();
	}

	typename std::list<std::pair<const Key, T>>::const_iterator cend() {
		return iteratorlist.cend();
	}

	typename std::list<std::pair<const Key, T>>::reverse_iterator rbegin() {
		return iteratorlist.rbegin();
	}

	typename std::list<std::pair<const Key, T>>::reverse_iterator rend() {
		return iteratorlist.rend();
	}

	typename std::list<std::pair<const Key, T>>::const_reverse_iterator crbegin() {
		return iteratorlist.crbegin();
	}

	typename std::list<std::pair<const Key, T>>::const_reverse_iterator crend() {
		return iteratorlist.crend();
	}
};

