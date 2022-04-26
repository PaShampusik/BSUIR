#pragma once

#include <cassert>

template<class T>
class Shared_Ptr;

template<class T>
class Weak_Ptr;

template<class T>
struct ControlBlock {
	int* shared_count = nullptr;
	int* weak_count = nullptr;
	//T* object = nullptr;

	template<class ... Args>
	ControlBlock(size_t count) {
	 	//object = new T(std::forward<Args>(args));
		shared_count = new int(count);
		weak_count = new int(0);
	};
};


template<class T>
class Shared_Ptr {
	T* OPtr = nullptr;
	int* count = nullptr;

	ControlBlock<T>* cptr = nullptr;

	template<class U, class ... Args>
	friend Shared_Ptr<U> Make_Shared(Args&& ... args);
	
	/*Shared_Ptr(ControlBlock<T>* ptr) : cptr(ptr)
	{

	}*/

public:

	Shared_Ptr() 
	{

	}

	explicit Shared_Ptr(T* ptr) 
	{
		cptr = new ControlBlock<T>(1);
		OPtr = ptr;

	}

	Shared_Ptr(const Shared_Ptr& ptr) 
	{
		~Shared_Ptr();
		cptr = ptr.cptr;
		this->OPtr = ptr.OPtr;
		(*cptr->shared_count)++;

	}

	explicit operator bool() const
	{
		return this->get() != nullptr;
	}

	void swap(Shared_Ptr<T>& other) 
	{
		using std::swap;
		swap(OPtr, other.OPtr);
	}

	int use_count() const  
	{
		return *(cptr->shared_count);
	}

	T* get() const  
	{
		return OPtr;
	}

	void operator=(Shared_Ptr& other) 
	{
		delete OPtr;
		OPtr = other.OPtr;
		other.OPtr = nullptr;
	}

	T& operator*() 
	{
		assert(OPtr);
		return *OPtr;
	}

	T* operator->() 
	{
		assert(OPtr);
		return OPtr;
	}

	~Shared_Ptr() 
	{
		if (!cptr) return;
		--(cptr->shared_count);

		if (cptr->shared_count == 0)
		{
			OPtr->~T();
			delete OPtr;
			if (cptr->weak_count == 0)
			{
				delete cptr;
			}
		}
	}

	friend class Weak_Ptr<T>;
};

template <class T, class ... Args>
Shared_Ptr<T> Make_Shared(Args&& ... args) 
{
	auto p = new ControlBlock<T>(1, std::forward<Args>(args)...);
	return Shared_Ptr;
}


template<class T>
class Weak_Ptr {
private:
	ControlBlock<T>* cptr = nullptr;

public:

	Weak_Ptr() 
	{

	}

	Weak_Ptr(const Shared_Ptr<T>& p) : cptr(p.cptr) 
	{
		(*(cptr->weak_count))++;
	}

	Weak_Ptr(const Weak_Ptr<T>& p) : cptr(p.cptr)
	{
		(*(cptr->weak_count))++;
	}

	void swap(Weak_Ptr<T>& other)
	{
		using std::swap;
		swap(cptr, other.cptr);
	}

	int use_count() const
	{
		return *(cptr->weak_count);
	}

	void reset(ControlBlock<T>* new_p)
	{
		delete cptr;
		cptr = new_p;
	}

	bool expired() const 
	{
		return cptr->shared_count == 0;
	}

	Shared_Ptr<T> lock() const {
		return Shared_Ptr<T>(cptr);
	}

	~Weak_Ptr() 
	{
		if (!cptr)return;
		--(cptr->weak_count);
		if (cptr->weak_count == 0 && cptr->shared_count == 0) 
		{
			delete cptr;
		}
	}

	friend class Shared_Ptr<T>;
};