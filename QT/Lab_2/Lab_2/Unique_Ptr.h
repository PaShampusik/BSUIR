#pragma once

#include<iostream>
#include<cassert>

template <class Type>
class My_unique_ptr
{

public:
	My_unique_ptr() {}

	My_unique_ptr(Type* pointer)
		: pointer(pointer) {}

	My_unique_ptr(My_unique_ptr& new_pointer)
		: pointer(new_pointer.pointer)
	{
		new_pointer.pointer = nullptr;
	}

	Type* get()
	{
		return pointer;
	}

	Type* release()
	{
		Type* temp = pointer;
		pointer = nullptr;
		return temp;
	}

	void reset(Type* new_p)
	{
		delete pointer;
		pointer = new_p;
	}

	void swap(My_unique_ptr* other)
	{
		My_unique_ptr* temp = pointer;
		pointer = other->pointer;
		other->pointer = temp;
		delete temp;
	}

	explicit operator bool()
	{
		return this->get() != nullptr;
	}

	My_unique_ptr operator=(My_unique_ptr&& new_pointer)
	{
		delete pointer;
		pointer = new_pointer.pointer;
		new_pointer.pointer = nullptr;
		return pointer;
	}

	Type& operator*()
	{
		assert(pointer);
		return *pointer;
	}

	Type* operator->()
	{
		assert(pointer);
		return pointer;
	}

	~My_unique_ptr()
	{
		delete pointer;
	}


	template <typename OType, typename... Args>
	friend My_unique_ptr<OType> make_unique_ptr(Args&&... args);

private:
	Type* pointer;
};


template <typename Type, typename... Args>
My_unique_ptr<Type> make_unique_ptr(Args&&... args)
{
	return My_unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}
    
