#include"DoubleLinkedList.h"
#include"AWL_Tree.h"



template<typename Key, typename T>
class AWL_Map
{

private:
	Tree<Key, T> tree;
	DoubleLinkedList<Key, T> list;
	int size;

public:

	AWL_Map()
	{
		size = 0;
	}

	void insert(Key key, T value)
	{
		if (tree.find(tree.getroot(), key) == nullptr)
		{
			tree.insert(tree.getroot(), key, value);
			list.insert(std::pair<Key, T>(key, value));
			list.sort();
			size++;
		}
		else
		{
		}
	}

	void remove(Key key)
	{
		if (tree.find(tree.getroot(), key) != nullptr)
		{
			tree.remove(tree.getroot(), key);
			list.remove(std::pair<Key, T>(key, tree.search(key)->value));
			list.sort();
			size--;
		}
	}

	T search(Key key)
	{
		for (auto i : list)
		{
			if (i->Data.first == key)
			{
				return i->Data.second;
			}
		}
		else
		{
			return nullptr;
		}
	}

	int getSize()
	{
		return size;
	}

	void print()
	{
		list.print();
	}

	Tree::TreeIterator begin()
	{
		return tree.begin();
	}
	
	Tree::TreeIterator end()
	{
		return tree.end();
	}
	
	Tree::TreeIterator rbegin()
	{
		return tree.rbegin();
	}

	Tree::TreeIterator rend()
	{
		return tree.rend();
	}

	Tree::TreeConstIterator cbegin()
	{
		return tree.cbegin();
	}

	Tree::TreeConstIterator cend()
	{
		return tree.cend();
	}

	Tree::TreeConstIterator crbegin()
	{
		return tree.crbegin();
	}

	Tree::TreeConstIterator crend()
	{
		return tree.crend();
	}
	
	DoubleLinkedList::ListIterator lbegin()
	{
		return list.begin();
	}
	
	DoubleLinkedList::ListIterator lend()
	{
		return list.end();
	}
};