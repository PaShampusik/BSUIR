#ifndef DOUBLELIST_H
#define DOUBLELIST_H


#include "Vector.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>



class DoubleLinkedListOnArray {
private:
    struct Node {
        Staff product;
        int next = -1;
        int prev = -1;
        Node() 
        {

        }
        Node(Staff pr, int n, int p)
            :product(pr), next(n), prev(p)
        {
			
        }
        bool compairingSurnames(QString name) {
            bool k = 1;
            int i = 0;
            while (product.getname().toStdString()[i] != ' ' && i < min(product.getname().toStdString().length(), name.length())) {
                if (product.getname().toStdString()[i] == name.toStdString()[i]) {}
                else
                {
                    k = 0;
                    return k;
                }
                ++i;
            }
            return 1;
        }
        
        int min(int a, int b) {
			if (a < b) return a;
			else return b;
        }
        
        ;
    };

    vector<Node> nodes;
    int head;
    int tail;
    int size;
public:
    DoubleLinkedListOnArray() {
        head = -1;
        tail = -1;
        size = 0;
    }


    ~DoubleLinkedListOnArray() {
        clear();
    }

    void clear() {
        while (size != 0) {
            remove(0);
        }
    }
    int getSize() {
        return size;
    }

    void add(Staff product) {
        if (size == 0) {
            head = 0;
            tail = 0;
            nodes.push_back(Node(product, -1, -1));
            size++;
        }
        else {
            nodes.push_back(Node{ product, -1, tail });
            nodes[tail].next = nodes.getSize() - 1;
            tail = nodes.getSize() - 1;
            size++;
        }


    }

    void pop() {
        if (size == 0) {
            return;
        }
        if (size == 1) {
            head = -1;
            tail = -1;
            size = 0;
            return;
        }
        int index = tail;
        tail = nodes[index].prev;
        nodes[tail].next = -1;
        nodes.pop_back();
        size--;
    }

    void remove(int index) {
        if (size == 1) {
            head = -1;
            tail = -1;
            nodes.erase(index);
            size--;
        }
        else if (index == head) {
            nodes.erase(index);
            tail = nodes.getSize() - 1;
            int i = index + 1;
            while (i < nodes.getSize()) {
                nodes[i].prev--;
                nodes[i].next--;
                i++;
            }
            nodes[index].prev = -1;
            nodes[index].next = 1;
            nodes[tail].next = -1;
            size--;
        }
        else if (index == tail) {
            nodes.erase(index);
            tail = nodes.getSize() - 1;
            nodes[tail].next = -1;
            size--;
        }
        else {
            nodes.erase(index);
            tail = nodes.getSize() - 1;
            int i = index + 1;
            while (i < nodes.getSize()) {
                nodes[i].prev--;
                nodes[i].next--;
                i++;
            }
            nodes[tail].next = -1;
            size--;
        }
    }

    void insert(int index, Staff product) {
        if (size == 0) {
            head = 0;
            tail = 0;
            nodes.push_back(Node(product, -1, -1));
            size++;
        }
        else if (index == 0) {
            nodes.insert(index, Node(product, 1, -1));
            nodes[nodes.getSize() - 1].next = nodes.getSize();
            nodes[1].prev = 0;
            tail = nodes.getSize() - 1;
            int i = index + 1;
            while (i < nodes.getSize()) {
                nodes[i].prev++;
                nodes[i].next++;
                i++;
            }
            nodes[nodes.getSize() - 1].next = -1;
            size++;
        }
        else if (index == size) {
            nodes.push_back(Node(product, -1, tail));
            nodes[tail].next = nodes.getSize() - 1;
            tail = nodes.getSize() - 1;
            size++;
        }
        else if (index == size - 1) {
            nodes.insert(index, Node(product, size, nodes[index].prev));
            tail = nodes.getSize() - 1;
            int i = index + 1;
            while (i < nodes.getSize()) {
                nodes[i].next++;
                nodes[i].prev++;
                i++;
            }
            nodes[nodes.getSize() - 1].next = -1;
            size++;
        }
        else {
            nodes.insert(index, Node(product, nodes[index].next, nodes[index].prev));
            tail = nodes.getSize() - 1;
            int i = index + 1;
            while (i < nodes.getSize()) {
                nodes[i].next++;
                nodes[i].prev++;
                i++;
            }
            nodes[nodes.getSize() - 1].next = -1;
            size++;
        }


    }

    int getHead() {
        return head;
    }
    int getTail() {
        return tail;
    }

    Staff getProduct(int index) {
        return nodes[index].product;
    }

    void print() {
        int index = head;
        while (index != -1) {
            //std::cout << nodes[index].product.name << " " << nodes[index].product.count << " " << nodes[index].product.price << " " << nodes[index].product.date << std::endl;
            index = nodes[index].next;
        }
    }

    void quickSort(vector<Node>& array, int low, int high)
    {
        int i = low;
        int j = high;
        Node pivot = array[(i + j) / 2];
        Staff temp;

        while (i < j)
        {
            while (array[i].product.getnumber().toDouble() < pivot.product.getnumber().toDouble())
                i++;
            while (array[j].product.getnumber().toDouble() > pivot.product.getnumber().toDouble())
                j--;
            if (i <= j)
            {
                temp = array[i].product;
                array[i].product = array[j].product;
                array[j].product = temp;
                i++;
                j--;
            }
        }
        if (j > low)
            quickSort(array, low, j);
        if (i < high)
            quickSort(array, i, high);
    }
    void quickSort() {
        quickSort(nodes, head, tail);
    }

    int isEmpty() {
        if (size == 0) {
            return 1;
        }
        else {
            return 0;
        }
    }

    DoubleLinkedListOnArray searchByNumber(QString number) {
        DoubleLinkedListOnArray result;
		int index = head, i = 0;
		while (index != -1) {
			if (nodes[index].product.getnumber().toLongLong() == number.toLongLong()) {
				result.nodes[i] = nodes[index];
                i++;
			}
			index = nodes[index].next;
		}
        return result;
    }

    DoubleLinkedListOnArray searchByName(QString name) {
        DoubleLinkedListOnArray result;
        int index = head, i = 0;
        while (index != -1) {
            if (nodes[i].compairingSurnames(name)){
                result.nodes[i] = nodes[index];
                i++;
            }
            index = nodes[index].next;
        }
        return result;
    }


    void deleteelementfromlist(QString Fullname, QString DepartmentNumber) {
        for (int i = 0; i < nodes.getSize(); i++)
        {
            if (nodes[i].product.fullname == Fullname && nodes[i].product.department_number == DepartmentNumber)
			{
				remove(i);
			}
        }
        
    }

    void save(DoubleLinkedListOnArray& list, QString filepath) {
        //output all data from list to a file with filepath filepath
        std::fstream file;
        if (!file.is_open())
        {
            file.open(filepath.toStdString(), std::ios::out | std::ios::trunc);
            file.clear();



           
            for (int i = 0; i < list.getTail(); i++)
            {
                file << list.getProduct(i).fullname.toStdString() << std::endl;
                file << list.getProduct(i).department_number.toStdString() << std::endl;				
                file << list.getProduct(i).position.toStdString() << std::endl;
                file << list.getProduct(i).date.toStdString() << std::endl;
                file << std::endl;
				
            }

            file.close();

        }

    }

};
#endif // DOUBLELIST_H
