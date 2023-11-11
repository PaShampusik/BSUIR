#pragma once


template<typename Key, typename Value>
class Map {
private:
	std::list<std::pair<const Key, Value>>* list_of_nodes;
	int size;
public:
	struct Node {
		std::pair<const Key, Value> data;
		short height;
		Node* left;
		Node* right;
		Node* parent;
		Node(Key key, Value value) : data(key, value), height(1), left(nullptr), right(nullptr), parent(nullptr) {}

		std::pair<const Key, Value> getdata() {
			return data;
		}
	};
	
	Node* root;

	struct ListIterator {
		typedef typename std::list<std::pair<Key, Value>>::iterator iterator;
		iterator it;
		ListIterator(iterator it) : it(it) {}
		std::pair<Key, Value> operator*() {
			return *it;
		}
		ListIterator operator++() {
			++it;
			return *this;
		}
		ListIterator operator++(int) {
			ListIterator tmp = *this;
			++it;
			return tmp;
		}
		bool operator==(const ListIterator& other) {
			return it == other.it;
		}
		bool operator!=(const ListIterator& other) {
			return it != other.it;
		}
	};

	struct ConstListIterator {
		typedef typename std::list<std::pair<Key, Value>>::const_iterator iterator;
		iterator it;
		ConstListIterator(iterator it) : it(it) {}
		std::pair<Key, Value> operator*() {
			return *it;
		}
		ConstListIterator operator++() {
			++it;
			return *this;
		}
		ConstListIterator operator++(int) {
			ConstListIterator tmp = *this;
			++it;
			return tmp;
		}
		bool operator==(const ConstListIterator& other) {
			return it == other.it;
		}
		bool operator!=(const ConstListIterator& other) {
			return it != other.it;
		}
	};

	struct Iterator {
		Node* current;
		Iterator(Node* node) : current(node) {}
		Iterator& operator++() {
			if (current->right != nullptr) {
				current = current->right;
				while (current->left != nullptr) {
					current = current->left;
				}
			}
			else {
				Node* parent = current->parent;
				while (parent != nullptr && current == parent->right) {
					current = parent;
					parent = parent->parent;
				}
				current = parent;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const Iterator& other) {
			return current == other.current;
		}
		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
		std::pair<Key, Value>& operator*() {
			return current->data;
		}
		std::pair<Key, Value>* operator->() {
			return &current->data;
		}
	};

	struct ConstIterator {
		Node* current;
		ConstIterator(Node* node) : current(node) {}
		ConstIterator& operator++() {
			if (current->right != nullptr) {
				current = current->right;
				while (current->left != nullptr) {
					current = current->left;
				}
			}
			else {
				Node* parent = current->parent;
				while (parent != nullptr && current == parent->right) {
					current = parent;
					parent = parent->parent;
				}
				current = parent;
			}
			return *this;
		}
		ConstIterator operator++(int) {
			ConstIterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const ConstIterator& other) {
			return current == other.current;
		}
		bool operator!=(const ConstIterator& other) {
			return current != other.current;
		}
		const std::pair<Key, Value>& operator*() {
			return current->data;
		}
		const std::pair<Key, Value>* operator->() {
			return &current->data;
		}
	};

	struct ReverseIterator {
		Node* current;
		ReverseIterator(Node* node) : current(node) {}
		ReverseIterator& operator++() {
			if (current->left != nullptr) {
				current = current->left;
				while (current->right != nullptr) {
					current = current->right;
				}
			}
			else {
				Node* parent = current->parent;
				while (parent != nullptr && current == parent->left) {
					current = parent;
					parent = parent->parent;
				}
				current = parent;
			}
			return *this;
		}
		ReverseIterator operator++(int) {
			ReverseIterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const ReverseIterator& other) {
			return current == other.current;
		}
		bool operator!=(const ReverseIterator& other) {
			return current != other.current;
		}
		std::pair<Key, Value>& operator*() {
			return current->data;
		}
		std::pair<Key, Value>* operator->() {
			return &current->data;
		}
	};

	struct ConstReverseIterator {
		Node* current;
		ConstReverseIterator(Node* node) : current(node) {}
		ConstReverseIterator& operator++() {
			if (current->left != nullptr) {
				current = current->left;
				while (current->right != nullptr) {
					current = current->right;
				}
			}
			else {
				Node* parent = current->parent;
				while (parent != nullptr && current == parent->left) {
					current = parent;
					parent = parent->parent;
				}
				current = parent;
			}
			return *this;
		}
		ConstReverseIterator operator++(int) {
			ConstReverseIterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const ConstReverseIterator& other) {
			return current == other.current;
		}
		bool operator!=(const ConstReverseIterator& other) {
			return current != other.current;
		}
		const std::pair<Key, Value>& operator*() {
			return current->data;
		}
		const std::pair<Key, Value>* operator->() {
			return &current->data;
		}
	};

	Node* rotateright(Node* p) // правый поворот вокруг p
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		if (p->left != nullptr)
		{
			p->left->parent = p;
		}
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node* rotateleft(Node* q) // левый поворот вокруг q
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		if (q->right != nullptr)
		{
			q->right->parent = q;
		}
		p->parent = q->parent;
		q->parent = p;
		fixheight(q);
		fixheight(p);
		return p;
	}

	short bfactor(Node* p)
	{
		return height(p->right) - height(p->left);
	}

	short height(Node* p)
	{
		return p ? p->height : 0;
	}

	void fixheight(Node* p) {
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	
	Node* findmax(Node* p) {
		if (p == nullptr) {
			return nullptr;
		}
		while (p->right != nullptr) {
			p = p->right;
		}
		return p;
	}

	Node* balance(Node* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	void TraverseInorder(Node* root) {
		if (root->left)
			TraverseInorder(root->left);

		//root->Print();

		if (root->right)
			TraverseInorder(root->right);
	}

	//set new root
	void setRoot(Node* newRoot) {
		root = newRoot;
	}

	int getsize() {
		return size;
	}

	Map() {
		root = nullptr;
		size = 0;
		list_of_nodes = new std::list<std::pair<const Key, Value>>();
	}

	~Map() {

	}

	Node*& getroot() {
		return root;
	}

	Node* insert(Node* p, Key k, Value data) //вставка ключа k и данных data в дерево с корнем p
	{
		if (this->find(root, k) != nullptr)
		{
			return nullptr;
		}
		if (!p) {
			size++;
			return new Node(k, data);
		}
		if (k < p->data.first) {
			p->left = insert(p->left, k, data);
			p->left->parent = p;
		}
		else {
			p->right = insert(p->right, k, data);
			p->right->parent = p;
		}
		list_of_nodes->push_back(std::pair<Key, Value>(k, data));
		//list_of_nodes->sort(list_of_nodes->front());
		return balance(p);
	}

	Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	Node* removemin(Node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		if (p->left != nullptr)
		{
			p->left->parent = p;
		}
		return balance(p);
	}

	Node* remove(Node* p, Key k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->data.first) {
			p->left = remove(p->left, k);
			if (p->left != nullptr)
			{
				p->left->parent = p;
			}
		}
		else if (k > p->data.first) {
			p->right = remove(p->right, k);
			if (p->right != nullptr)
			{
				p->right->parent = p;
			}
		}
		else
		{
			if (size == 2) {
				if (p->left)
				{
					size--;
					return p->left;
				}
				else if (p->parent) {
					size--;
					return nullptr;
				}
				else
				{
					size--;
					return p->right;
				}
			}
			if (size == 1)
			{
				size--;
				return nullptr;
			}
			Node* q = p->left;
			Node* r = p->right;
			list_of_nodes->remove(p->getdata());
			//list_of_nodes->sort(list_of_nodes->front(), list_of_nodes->back());
			delete p;
			if (!r) return q;
			Node* min = findmin(r);
			min->right = removemin(r);
			if (min->right != nullptr)
			{
				min->right->parent = min;
			}
			min->left = q;

			min->left->parent = min;
			return balance(min);
		}
		size--;
		return balance(p);
	}

	Node* find(Node* p, Key k) // поиск ключа k в дереве p
	{
		if (!p) return nullptr;

		if (k < p->data.second)
		{
			if (p->left == nullptr)
				return nullptr;
			return find(p->left, k);
		}
		else if (k > p->data.second)
		{
			if (p->right == nullptr)
				return nullptr;
			return find(p->right, k);
		}
		else
		{
			return p;
		}
	}

	Iterator begin() {
		return Iterator(findmin(root));
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	ConstIterator cbegin() const {
		return ConstIterator(findmin(root));
	}

	ConstIterator cend() const {
		return ConstIterator(nullptr);
	}

	ReverseIterator rbegin() {
		return ReverseIterator(findmax(root));
	}

	ReverseIterator rend() {
		return ReverseIterator(nullptr);
	}

	ConstReverseIterator crbegin() const {
		return ConstReverseIterator(findmax(root));
	}

	ConstReverseIterator crend() const {
		return ConstReverseIterator(nullptr);
	}

	ListIterator list_begin() {
		return ListIterator(list_of_nodes->begin());
	}

	ListIterator list_end() {
		return ListIterator(list_of_nodes->end());
	}

	ConstListIterator list_cbegin() const {
		return ConstListIterator(list_of_nodes->cbegin());
	}

	ConstListIterator list_cend() const {
		return ConstListIterator(list_of_nodes->cend());
	}
};
