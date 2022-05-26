#pragma once
#include <string>
#include <iostream>

template <int SIZE>
class Bitset {
private:
	unsigned long long Bits[(SIZE + 63) / 64];
	size_t size = (SIZE + 63) / 64;

	void trim() {
		bool need_to_correct_last_element_bits = SIZE == 0 || SIZE % 64 != 0;
		if (need_to_correct_last_element_bits) {
			Bits[size - 1] &= (1ULL << SIZE % 64) - 1;
		}
	}

public:

	class reference {
	private:
		Bitset& refer;
		size_t position;

	public:

		reference(Bitset& refer, size_t position) : refer(refer), position(position) {}

		reference& operator=(bool value) {

			refer.set(position, value);
			return *this;
		}

		reference& operator=(const reference& other) {
			refer.set(position, other.refer.test(position));
			return *this;
		}

		operator bool() const {
			return refer.test(position);
		}

		reference& operator~()
		{
			refer.flip(position);
			return *this;
		}

		reference& flip() {
			refer.flip(position);
			return *this;
		}
	};

	Bitset() {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] = 0ULL;
		}
	}

	Bitset(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] = other.Bits[i];
		}
	}

	Bitset(const char* str)
	{
		reset();
		size_t length = strlen(str);
		if (length > SIZE)
		{
			length = SIZE;
		}
		for (size_t i = 0; i < length; i++)
		{
			if (str[length - i - 1] == '1')
			{
				set(i);
			}
		}
	}

	Bitset(unsigned long long value)
	{
		reset();
		Bits[0] = value;
		trim();
	}

	bool test(size_t num) {
		if (num >= SIZE)
		{
			throw std::out_of_range("Out of range");
		}
		size_t index = num / 64;
		size_t offset = num % 64;
		return (Bits[index] & (1ULL << offset)) != 0;
	}

	bool all() {
		if (SIZE == 0)
		{
			return true;
		}
		bool padding = SIZE % 64 == 0;
		for (size_t i = 0; i < size - 1 + padding; i++)
		{
			if (Bits[i] != ~0ULL)
			{
				return false;
			}
		}
		return padding || Bits[size - 1] == (1ULL << (SIZE % 64)) - 1;
	}

	bool any() {
		for (size_t i = 0; i < size; i++)
		{
			if (Bits[i] != 0ULL)
			{
				return true;
			}
		}
		return false;
	}

	bool none() {
		return !any();
	}

	size_t count() {
		size_t res = 0;
		for (size_t i = 0; i < size; i++)
		{
			res += __popcnt64(Bits[i]);
		}
		return res;
	}

	size_t get_size() {
		return SIZE;
	}

	Bitset& flip() {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] = ~Bits[i];
		}
		trim();
		return *this;
	}

	Bitset& flip(size_t position) {
		Bits[position / 64] ^= (1ULL << (position % 64));
		return *this;
	}

	Bitset& set() {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] = ULLONG_MAX;
		}
		trim();
		return *this;
	}

	Bitset& set(size_t position, bool value = true) {
		if (value)
		{
			Bits[position / 64] |= (1ULL << (position % 64));
		}
		else
		{
			Bits[position / 64] &= ~(1ULL << (position % 64));

		}
		return *this;
	}

	Bitset& reset() {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] = 0ULL;
		}
		return *this;
	}

	Bitset& reset(size_t position) {
		Bits[position / 64] &= ~(1ULL << (position % 64));
		return *this;
	}

	std::string to_string() {
		std::string res;
		res.reserve(SIZE);
		for (size_t i = SIZE; i > 0; )
		{
			i--;
			if (test(i))
			{
				res += '1';
			}
			else
			{
				res += '0';
			}
		}
		return res;
	}
	             
	unsigned long long to_ullong() const {
		if (SIZE == 0)
		{
			return 0;
		}
		if (SIZE > 64)
		{
			for (size_t i = 1; i < size; i++)
			{
				if (Bits[i] != 0ULL)
				{
					throw std::out_of_range("Out of range");
				}
			}
		}
		return Bits[0];

	}

	unsigned long to_ulong() const {
		bool bits_zero = SIZE == 0;
		bool bits_small = SIZE <= 32;
		bool bits_large = SIZE > 64;
		if (bits_zero)
		{
			return 0;
		}
		if (bits_small)
		{
			return static_cast<unsigned long>(Bits[0]);
		}
		if (bits_large)
		{
			for (size_t i = 1; i < size; i++)
			{
				if (Bits[i] != 0ULL)
				{
					throw std::out_of_range("Out of range");
				}
			}
		}
		return static_cast<unsigned long>(Bits[0]);
	}

	reference operator[](size_t num) {
		if (num >= SIZE)
		{
			throw std::out_of_range("Index out of range");
		}
		return reference(*this, num);
	}

	bool operator[](size_t num) const {
		if (num >= SIZE)
		{
			throw std::out_of_range("Index out of range");
		}
		return Bits[num / 64] & (1ULL << (num % 64));
	}

	bool operator==(const Bitset& oi) {
		if (SIZE != oi.SIZE)
		{
			return false;
		}
		for (size_t i = 0; i < size; i++)
		{
			if (Bits[i] != oi.Bits[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Bitset& oi) {
		return !(*this == oi);
	}

	Bitset operator~() {
		Bitset res(*this);
		res.flip();
		return res;
	}


	Bitset& operator&=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] &= other.Bits[i];
		}
		return *this;
	}

	/*template <int SIZE>
	inline Bitset<SIZE> operator^(const Bitset<SIZE>& lhs, const Bitset<SIZE>& rhs) {
		Bitset<SIZE> res(lhs);
		res ^= rhs;
		return res;
	}*/
	
	Bitset& operator|=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] |= other.Bits[i];
		}
		return *this;
	}

	Bitset& operator^=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			Bits[i] ^= other.Bits[i];
		}
		return *this;
	}

	Bitset& cycle_(size_t position)
	{
		for (size_t i = 0; i < size; i++)
		{

			if (this->test(size - 1))
			{
				Bits[i] <<= (SIZE % 64);
				this->set(0, 1);
			}
			else this->set(0, 0);
		}
	}
};

template <int SIZE>
inline Bitset<SIZE> operator|(const Bitset<SIZE>& lhs, const Bitset<SIZE>& rhs) {
	Bitset<SIZE> res(lhs);
	res |= rhs;
	return res;
}

template <int SIZE>
inline Bitset<SIZE> operator&(const Bitset<SIZE>& lhs, const Bitset<SIZE>& rhs) {
	Bitset<SIZE> res(lhs);
	res &= rhs;
	return res;
}





