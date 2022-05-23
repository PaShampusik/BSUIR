#pragma once
template<typename T, typename data>
struct TreeNode {
	std::pair<T, data> data;
	short height;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNode(T key, data value) {
		data = std::make_pair(key, value);		
		this->height = 1;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};

template<typename T, typename data>
class Tree {
private:
	TreeNode<T, data>* root;
	int size;

	TreeNode<T, data>* rotateright(TreeNode<T, data>* p) // правый поворот вокруг p
	{
		TreeNode<T, data>* q = p->left;
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

	TreeNode<T, data>* rotateleft(TreeNode<T>* q) // левый поворот вокруг q
	{
		TreeNode<T, data>* p = q->right;
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

	short bfactor(TreeNode<T, data>* p)
	{
		return height(p->right) - height(p->left);
	}

	short height(TreeNode<T, data>* p)
	{
		return p ? p->height : 0;
	}

	void fixheight(TreeNode<T, data>* p) {
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

public:
	Tree() {
		root = nullptr;
		size = 0;
	}
	
	
	TreeNode<T, data>* balance(TreeNode<T, data>* p) // балансировка узла p
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
	
	void TraverseInorder(TreeNode<T, data>* root) {
		if (root->left)
			TraverseInorder(root->left);

		//root->Print();

		if (root->right)
			TraverseInorder(root->right);
	}

	//set new root
	void setRoot(TreeNode<T, data>* newRoot) {
		root = newRoot;
	}
	

	int getsize() {
		return size;
	}

	Tree() {
		root = nullptr;
		size = 0;
	}

	~Tree() {

	}

	TreeNode<T, data>*& getroot() {
		return root;
	}


	TreeNode<T, data>* insert(TreeNode<T, data>* p, T k, data t) //вставка ключа k в дерево с корнем p
	{
		if (!p) {
			size++;
			return new TreeNode<T, data>(k, t);
		}
		if (k < p->key) {
			p->left = insert(p->left, k, t);
			p->left->parent = p;
		}
		else {
			p->right = insert(p->right, k, t);
			p->right->parent = p;
		}
		return balance(p);
	}

	TreeNode<T, data>* findmin(TreeNode<T, data>* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}
	
	TreeNode<T, data>* findmax(TreeNode<T, data>* p) {
		return p->right ? findmax(p->right) : p;
	}

	TreeNode<T, data>* removemin(TreeNode<T, data>* p) // удаление узла с минимальным ключом из дерева p
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

	TreeNode<T, data>* remove(TreeNode<T, data>* p, T k) // удаление ключа k из дерева p
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
			TreeNode<T, data>* q = p->left;
			TreeNode<T, data>* r = p->right;
			delete p;
			if (!r) return q;
			TreeNode<T, data>* min = findmin(r);
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

	TreeNode<T, data>* find(TreeNode<T, data>* p, T k) // поиск ключа k в дереве p
	{
		if (!p) return nullptr;

		if (k < p->key)
		{
			if (p->left == nullptr)
				return nullptr;
			return find(p->left, k);
		}
		else if (k > p->key)
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

	class TreeIterator {
	private:
		TreeNode* current;
	public:
		TreeIterator(TreeNode* c) : current(c) {}
		TreeIterator(const TreeIterator& it) : current(it.current) {}
		TreeIterator& operator=(const TreeIterator& it) {
			current = it.current;
			return *this;
		}
		TreeNode& operator*() const { return *(current); }
		TreeNode* operator->() const { return current; }

		bool operator==(const TreeIterator& it) const { return current == it.current; }
		bool operator!=(const TreeIterator& it) const { return current != it.current; }

		TreeIterator& operator++() {
			if (current->right != nullptr) {
				current = current-> > findmin(current->right);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key < key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeIterator operator++(int) {
			TreeIterator it = *this;
			++(*this);
			return it;
		}

		TreeIterator& operator--() {
			if (current->left != nullptr) {
				current = current-> > Tree::findmax(current->left);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key > key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeIterator operator--(int) {
			TreeIterator it = *this;
			--(*this);
			return it;
		}
	};


	class TreeConstIterator {
	private:
		TreeNode* current;
	public:
		TreeConstIterator(const TreeNode* c) : current(c) {}
		TreeConstIterator(const TreeConstIterator& it) : current(it.current) {}
		TreeConstIterator& operator=(const TreeConstIterator& it) {
			current = it.current;
			return *this;
		}
		const TreeNode& operator*() const { return *(current); }
		const TreeNode* operator->() const { return current; }

		bool operator==(const TreeConstIterator& it) const { return current == it.current; }
		bool operator!=(const TreeConstIterator& it) const { return current != it.current; }

		TreeConstIterator& operator++() {
			if (current->right != nullptr) {
				current = current-> > Tree::findmin(current->right);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key < key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeConstIterator operator++(int) {
			TreeConstIterator it = *this;
			++(*this);
			return it;
		}

		TreeConstIterator& operator--() {
			if (current->left != nullptr) {
				current = current-> > Tree::findmax(current->left);
			}
			else {
				KeyType key = current->key;
				current = current->parent;
				while (current != nullptr && current->key > key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeConstIterator operator--(int) {
			TreeConstIterator it = *this;
			--(*this);
			return it;
		}
	};

	class TreeReverseIterator {
	private:
		TreeNode* current;
	public:
		TreeReverseIterator(TreeNode* c) : current(c) {}
		TreeReverseIterator(const TreeReverseIterator& it) : current(it.current) {}
		TreeReverseIterator& operator=(const TreeReverseIterator& it) {
			current = it.current;
			return *this;
		}
		TreeNode& operator*() const { return *(current); }
		TreeNode* operator->() const { return current; }

		bool operator==(const TreeReverseIterator& it) const { return current == it.current; }
		bool operator!=(const TreeReverseIterator& it) const { return current != it.current; }

		TreeReverseIterator& operator++()
		{
			if (current == nullptr) {
				current = current-> > Tree::findmax(current);
			}
			else if (current->left != nullptr) {
				current = current-> > Tree::findmax(current->left);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key > key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeReverseIterator operator++(int) {
			TreeReverseIterator it = *this;
			++(*this);
			return it;
		}

		TreeReverseIterator& operator--() {
			if (current->right != nullptr) {
				current = current-> > Tree::findmin(current->right);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key < key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeReverseIterator operator--(int) {
			TreeReverseIterator it = *this;
			--(*this);
			return it;
		}
	};

	class TreeConstReverseIterator {
	private:
		TreeNode<T, data>* current;
	public:
		TreeConstReverseIterator(const TreeNode<T, data>* c) : current(c) {}
		TreeConstReverseIterator(const TreeConstReverseIterator& it) : current(it.current) {}
		TreeConstReverseIterator& operator=(const TreeConstReverseIterator& it) {
			current = it.current;
			return *this;
		}
		const TreeNode& operator*() const { return *(current); }
		const TreeNode* operator->() const { return current; }

		bool operator==(const TreeConstReverseIterator& it) const { return current == it.current; }
		bool operator!=(const TreeConstReverseIterator& it) const { return current != it.current; }

		TreeConstReverseIterator& operator++()
		{
			if (current == nullptr) {
				current = current-> > Tree::findmax(current);
			}
			else if (current->left != nullptr) {
				current = current-> > Tree::findmax(current->left);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key > key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeConstReverseIterator operator++(int) {
			TreeConstReverseIterator it = *this;
			++(*this);
			return it;
		}

		TreeConstReverseIterator& operator--() {
			if (current->right != nullptr) {
				current = current->Tree::findmin(current->right);
			}
			else {
				T key = current->key;
				current = current->parent;
				while (current != nullptr && current->key < key) {
					current = current->parent;
				}
			}

			return *this;
		}

		TreeConstReverseIterator operator--(int) {
			TreeConstReverseIterator it = *this;
			--(*this);
			return it;
		}
	};	
	
	TreeIterator& begin() {
		return TreeIterator(root);
	}
	
	TreeIterator& end() {
		return TreeIterator(nullptr);
	}
	
	TreeReverseIterator& rbegin() {
		return TreeReverseIterator(root);
	}

	TreeReverseIterator& rend() {
		return TreeReverseIterator(nullptr);
	}

	TreeConstIterator& cbegin() const {
		return TreeConstIterator(root);
	}
	
	TreeConstIterator& cend() const {
		return TreeConstIterator(nullptr);
	}
	
	TreeConstReverseIterator& crbegin() const {
		return TreeConstReverseIterator(root);
	}

	TreeConstReverseIterator& crend() const {
		return TreeConstReverseIterator(nullptr);
	}
};