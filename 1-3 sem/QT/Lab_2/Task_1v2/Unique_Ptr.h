#pragma once

#include<iostream>
#include<cassert>

template <class Type>
class Unique_Ptr
{

public:
	Unique_Ptr() {}

	Unique_Ptr(Type* pointer)
		: ptr(pointer) {}

	Unique_Ptr(Unique_Ptr& new_pointer)
		: ptr(new_pointer.ptr)
	{
		new_pointer.ptr = nullptr;
	}

	~Unique_Ptr()
	{
		delete ptr;
	}

	Unique_Ptr(const Unique_Ptr&) = delete;
	void operator=(const Unique_Ptr&) = delete;

	Type* get()
	{
		return ptr;
	}

	Type* release()
	{
		Type* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	void reset(Type* new_p)
	{
		delete ptr;
		ptr = new_p;
	}

	void swap(Unique_Ptr* other)
	{
		Unique_Ptr* temp = ptr;
		ptr = other->ptr;
		other->ptr = temp;
		delete temp;
	}

	explicit operator bool()
	{
		return this->get() != nullptr;
	}

	Unique_Ptr operator=(Unique_Ptr&& new_pointer)
	{
		delete ptr;
		ptr = new_pointer.ptr;
		new_pointer.ptr = nullptr;
		return ptr;
	}

	Type& operator*()
	{
		assert(ptr);
		return *ptr;
	}

	Type* operator->()
	{
		assert(ptr);
		return ptr;
	}



	template <typename OType, typename... Args>
	friend Unique_Ptr<OType> make_unique_ptr(Args&&... args);

private:
	Type* ptr;
};


template <typename Type, typename... Args>
Unique_Ptr<Type> make_unique_ptr(Args&&... args)
{
	return Unique_Ptr<Type>(new Type(std::forward<Args>(args)...));
}


