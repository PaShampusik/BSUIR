#pragma once

template<typename Key>
class Set {
private:
	std::list<Key>* list_of_nodes;
	int size;
public:
	struct Node {
		Key data;
		short height;
		Node* left;
		Node* right;
		Node* parent;
		Node(Key key) : data(key), height(1), left(nullptr), right(nullptr), parent(nullptr) {}

		Key getdata() {
			return data;
		}
	};
	
	Node* root;

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
		Key& operator*() {
			return current->data;
		}
		Key* operator->() {
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
		const Key& operator*() {
			return current->data;
		}
		const Key* operator->() {
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
		Key& operator*() {
			return current->data;
		}
		Key* operator->() {
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
		const Key& operator*() {
			return current->data;
		}
		const Key* operator->() {
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

	Set() {
		root = nullptr;
		size = 0;
		list_of_nodes = new std::list<Key>();
	}

	~Set() {

	}

	Node*& getroot() {
		return root;
	}

	Node* insert(Node* p, Key k) //вставка ключа k и данных в дерево с корнем p
	{
		if (this->find(root, k) != nullptr)
		{
			return nullptr;
		}
		if (!p) {
			size++;
			return new Node(k);
		}
		if (k < p->data) {
			p->left = insert(p->left, k);
			p->left->parent = p;
		}
		else {
			p->right = insert(p->right, k);
			p->right->parent = p;
		}
		list_of_nodes->push_front(k);
		//list_of_nodes->sort(list_of_nodes->front(), list_of_nodes->back());
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

	Node* findmax(Node* p) {
		return p->right ? findmax(p->right) : p;
	}

	Node* remove(Node* p, Key k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->data) {
			p->left = remove(p->left, k);
			if (p->left != nullptr)
			{
				p->left->parent = p;
			}
		}
		else if (k > p->data) {
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
			list_of_nodes->sort();
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

		if (k < p->data)
		{
			if (p->left == nullptr)
				return nullptr;
			return find(p->left, k);
		}
		else if (k > p->data)
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

	typename std::list<std::pair<Key, char>>::iterator list_begin() {
		return list_of_nodes->begin();
	}

	typename std::list<std::pair<Key, char>>::iterator list_end() {
		return list_of_nodes->end();
	}

	typename std::list<std::pair<Key, char>>::const_iterator list_cbegin() const {
		return list_of_nodes->cbegin();
	}

	typename std::list<std::pair<Key, char>>::const_iterator list_cend() const {
		return list_of_nodes->cend();
	}
};
