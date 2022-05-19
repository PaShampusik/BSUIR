#pragma once
#include "DoubleLinkedList.h"
#include <functional>


template<typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class HashTable {
private:
	int size = 100;
	int count;
	int hash(Key key) {
		return Hash()(key) % size;
	}
public:
	DoubleLinkedList<pair<const Key, T>>* table;
	
	HashTable() {
		this->size = size;
		count = 0;		
		table = new DoubleLinkedList<pair<const Key, T>>[size];
		
	}
	~HashTable() {
		delete[] table;
	}
	void insert(Key key, T data) {
		int index = hash(key);
		table[index].push_back(new Node(std::pair<const Key, T>(key, data)));
		count++;
	}
	bool find(Key key, T data) {
		auto& bucket = table[hash(key)];
		Node<std::pair<const Key, T>>* temp = bucket.getHead();
		while (temp != nullptr) {
			if (temp->data.second == data) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	
	void remove(Key key, T data) {
		int index = hash(key);
		table[index].deleteNode(std::pair<const Key, T>(key, data));
	}

	
	int FindMin() {
		int min = 1000, ind = -1;
		
		for (int i = 0; i < size; i++)
		{
			Node<std::pair<const Key, T>>* temp = table[i].getHead();
			while (temp != nullptr) {
				if (temp->data.second < min) {
					min = temp->data.second;
					ind = i;
				}
				temp = temp->next;
			}	
		}
		return ind + 1;
	}
	
	
	void rehash() {
		DoubleLinkedList<pair<const Key, T>>* temp = table;
		table = new DoubleLinkedList<pair<const Key, T>>[size * 2];
		size *= 2;
		for (int i = 0; i < size / 2; i++)
		{
			Node<std::pair<const Key, T>>* temp2 = temp[i].getHead();
			while (temp2 != nullptr) {
				insert(temp2->data.first, temp2->data.second);
				temp2 = temp2->next;
			}
		}
		delete[] temp;
	}

	void clear() {
		for (int i = 0; i < size; i++)
		{
			table[i].clear();
		}
	}
};

