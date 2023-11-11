#pragma once
#include <iostream>
#include <deque>

template<typename T>
class Deque
{
public:
	template <typename T>
	struct DequeIterator
	{
	public:

		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;


		T* current_;
		T* start;
		T* last;
		T** node;

		static size_t buffur_size() { return 10; }

		DequeIterator(T* element, T** new_node)
			: current_(element), start(*new_node), last(*new_node + buffur_size()), node(new_node) {}

		DequeIterator()
			: current_(nullptr), start(nullptr), last(nullptr), node(nullptr) {}

		DequeIterator(const DequeIterator& other)
			: current_(other.current_), start(other.start), last(other.last), node(other.node) {}
		void set_node(T** new_node)
		{
			node = new_node;
			start = *new_node;
			last = start + buffur_size() - 1;
		}

		void set_node(T** new_node, T* element)
		{
			node = new_node;
			start = *new_node;
			last = start + buffur_size() - 1;
			current_ = element;
		}

		reference operator*() { return *current_; }
		pointer operator->() { return current_; }
		bool operator==(const DequeIterator& other) const { return current_ == other.current_; }
		bool operator!=(const DequeIterator& other) const { return !(*this == other); }
		bool operator<(const DequeIterator& other) const { return current_ < other.current_; }

		DequeIterator& operator++()
		{
			if (current_ == last)
			{
				set_node(node + 1);
				current_ = start;
				return *this;
			}
			current_++;
			return *this;
		}
		DequeIterator operator++(int)
		{
			DequeIterator temp = *this;
			++(*this);
			return temp;
		}
		DequeIterator& operator--()
		{
			if (current_ == start)
			{
				set_node(node - 1);
				current_ = last;
			}
			current_--;
			return *this;
		}
		DequeIterator operator--(int)
		{
			DequeIterator temp = *this;
			--(*this);
			return temp;
		}
		reference operator[](ptrdiff_t n) const
		{
			return *(*this + n);
		}
	};
public:

	typedef T value_type;
	typedef DequeIterator<T> iterator;
	typedef value_type* pointer;
	typedef value_type& reference;

	static size_t buffer_size() { return 10; }
	static size_t initial_map_size() { return 8; }
	size_t max_size() const { return size_t(-1); }

	T** map;
	iterator begin;
	iterator end;
	size_t map_size;
	size_t capacity;

	Deque()
	{
		map_size = 1;
		capacity = buffer_size() * map_size;
		map = new T * [map_size];
		for (size_t i = 0; i < map_size; i++)
		{
			map[i] = new T[buffer_size()];
		}
		begin = iterator(map[0], map);
		end = iterator(map[0], map);
	}

	~Deque(){}

	iterator Begin()
	{
		return begin;
	}

	iterator End()
	{
		return end;
	}

	reference front()
	{
		return *begin;
	}

	reference back()
	{
		auto temp = end;
		--temp;
		return *temp;
	}

	bool empty() const
	{
		return end.current_ == begin.current_;
	}

	size_t size() const
	{
		size_t size_ = 0;
		for (auto it = begin; it != end; ++it)
		{
			size_++;
		}
		return size_;
	}

	void clear()
	{
		if (!empty())
		{
			*this = Deque();
		}
	}

	reference operator[](size_t index)
	{
		return begin[ptrdiff_t(index)];
	}

	void resize()
	{
		size_t new_map_size = map_size + 1;
		capacity = buffer_size() * new_map_size;
		T** new_map = new T * [new_map_size];
		for (size_t i = 0; i < new_map_size; i++)
		{
			new_map[i] = new T[buffer_size()];
		}
		for (size_t i = 0; i < map_size; i++)
		{
			for (size_t j = 0; j < buffer_size(); j++)
			{
				new_map[i][j] = map[i][j];
			}
		}
		auto temp2 = begin.current_ - begin.start;
		delete[] map;
		map = new_map;
		begin.set_node(map, map[0] + temp2);
		end.set_node(map + map_size, map[map_size]);
		map_size = new_map_size;
	}

	void resize_front()
	{
		size_t new_map_size = map_size + 1;
		capacity = buffer_size() * new_map_size;
		T** new_map = new T * [new_map_size];
		for (size_t i = 0; i < new_map_size; i++)
		{
			new_map[i] = new T[buffer_size()];
		}
		for (size_t i = 0, k = 1; i < map_size; i++, k++)
		{
			for (size_t j = 0; j < buffer_size(); j++)
			{
				new_map[k][j] = map[i][j];
			}
		}
		auto temp2 = end.current_ - end.start;
		delete[] map;
		map = new_map;
		begin.set_node(map, map[0] + buffer_size() - 1);
		end.set_node(map + map_size, map[map_size] + temp2);
		map_size = new_map_size;
	}

	void push_back(const T& value)
	{
		if (end.current_ == end.last)
		{
			*(end.current_) = value;
			resize();
		}
			*(end.current_) = value;
			end.current_++;
	}

	void push_front(const T& value)
	{
		if (begin.current_ != begin.start)
		{
			begin.current_--;
			*(begin.current_) = value;
		}
		else
		{
			resize_front();
			*(begin.current_) = value;
		}
	}

	void delete_back()
	{
		size_t new_map_size = map_size - 1;
		capacity = buffer_size() * new_map_size;
		T** new_map = new T * [new_map_size];
		for (size_t i = 0; i < new_map_size; i++)
		{
			new_map[i] = new T[buffer_size()];
		}
		for (size_t i = 0; i < new_map_size; i++)
		{
			for (size_t j = 0; j < buffer_size(); j++)
			{
				new_map[i][j] = map[i][j];
			}
		}
		auto temp2 = begin.current_ - begin.start;
		delete[] map;
		map = new_map;
		begin.set_node(map, map[0] + temp2);
		end.set_node(map + map_size - 2, map[map_size - 2] + buffer_size() - 1);
		map_size = new_map_size;
	}

	void pop_back()
	{
		if (!empty())
		{
			if (end.current_ != end.start)
			{
				end.current_--;
			}
			else
			{
				delete_back();
			}
		}
	}

	void delete_front()
	{
		size_t new_map_size = map_size - 1;
		capacity = buffer_size() * new_map_size;
		T** new_map = new T * [new_map_size];
		for (size_t i = 0; i < new_map_size; i++)
		{
			new_map[i] = new T[buffer_size()];
		}
		for (size_t i = 0, k = 1; i < new_map_size; i++, k++)
		{
			for (size_t j = 0; j < buffer_size(); j++)
			{
				new_map[i][j] = map[k][j];
			}
		}
		auto temp2 = end.current_ - end.start;
		delete[] map;
		map = new_map;
		begin.set_node(map, map[0]);
		end.set_node(map + map_size - 2, map[map_size - 2] + temp2);
		map_size = new_map_size;
	}

	void pop_front()
	{
		if (!empty())
		{
			if (begin.current_ != begin.last)
			{
				begin.current_++;
			}
			else
			{
				delete_front();
			}

		}
	}
};



