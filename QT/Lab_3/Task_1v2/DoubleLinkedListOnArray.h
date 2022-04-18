#ifndef DOUBLELIST_H
#define DOUBLELIST_H


#include "Vector.h"
#include <string>

struct Product {
    std::string name = "Milk";
    int count = 2;
    int price = 100;
    std::string date = "20.01.2001";
};

class DoubleList {
private:
    struct Node {
        Product product;
        int next = -1;
        int prev = -1;
        Node() {

        }
        Node(Product pr, int n, int p)
            :product(pr), next(n), prev(p)
        {
        };
    };
	
    vector<Node> nodes;
    int head;
    int tail;
    int size;
public:
    DoubleList() {
        head = -1;
        tail = -1;
        size = 0;
    }


    ~DoubleList() {
        listClear();
    }

    void listClear() {
        while (size != 0) {
            remove(0);
        }
    }
    int getSize() {
        return size;
    }

    void add(Product product) {
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

    void insert(int index, Product product) {
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

    Product getProduct(int index) {
        return nodes[index].product;
    }

    void print() {
        int index = head;
        while (index != -1) {
            //std::cout << nodes[index].product.name << " " << nodes[index].product.count << " " << nodes[index].product.price << " " << nodes[index].product.date << std::endl;
            index = nodes[index].next;
        }
    }

    void _quickSort(vector<Node>& array, int low, int high)
    {
        int i = low;
        int j = high;
        Node pivot = array[(i + j) / 2];
        Product temp;

        while (i < j)
        {
            while (array[i].product.price < pivot.product.price)
                i++;
            while (array[j].product.price > pivot.product.price)
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
            _quickSort(array, low, j);
        if (i < high)
            _quickSort(array, i, high);
    }
    void quickSort() {
        _quickSort(nodes, head, tail);
    }
};

#endif // DOUBLELIST_H
