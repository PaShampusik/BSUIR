#pragma once
template<typename T>
struct Node {
	T key;
	short height;
	Node* left;
	Node* right;
	Node* parent;
	Node(T data) : key(data), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

template<typename T>
class Tree {


	Node<T>* root;
	int size;

	Node<T>* rotateright(Node<T>* p) // правый поворот вокруг p
	{
		Node<T>* q = p->left;
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

	Node<T>* rotateleft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->right;
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

	short bfactor(Node<T>* p)
	{
		return height(p->right) - height(p->left);
	}

	short height(Node<T>* p)
	{
		return p ? p->height : 0;
	}

	void fixheight(Node<T>* p) {
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	Node<T>* balance(Node<T>* p) // балансировка узла p
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


public:
	void TraverseInorder(Node<T>* root) {
		if (root->left)
			TraverseInorder(root->left);

		//root->Print();

		if (root->right)
			TraverseInorder(root->right);
	}

	//set new root
	void setRoot(Node<T>* newRoot) {
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

	Node<T>*& getroot() {
		return root;
	}


	Node<T>* insert(Node<T>* p, T k) //вставка ключа k в дерево с корнем p
	{
		if (!p) {
			size++;
			return new Node<T>(k);
		}
		if (k < p->key) {
			p->left = insert(p->left, k);
			p->left->parent = p;
		}
		else {
			p->right = insert(p->right, k);
			p->right->parent = p;
		}
		return balance(p);
	}

	Node<T>* findmin(Node<T>* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	Node<T>* removemin(Node<T>* p) // удаление узла с минимальным ключом из дерева p
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

	Node<T>* remove(Node<T>* p, T k) // удаление ключа k из дерева p
	{	
		if (!p) return 0;
		if (k < p->key) {
			p->left = remove(p->left, k);
			if (p->left != nullptr)
			{
				p->left->parent = p;
			}
		}
		else if (k > p->key) {
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
			Node<T>* q = p->left;
			Node<T>* r = p->right;
			delete p;
			if (!r) return q;
			Node<T>* min = findmin(r);
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

	Node<T>* find(Node<T>* p, T k) // поиск ключа k в дереве p
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
};