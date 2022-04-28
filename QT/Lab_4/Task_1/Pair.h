#pragma once

template<typename T1, typename T2>
struct pair {
	
public:	
	T1 first;
	T2 second;
	pair(T1 first, T2 second) : first_element(first), second_element(second) {}
	
	&pair operator=(const pair &other) {
		first_element = other.first_element;
		second_element = other.second_element;
		return *this;
	}
	
	bool operator==(const pair &other) {
		return first_element == other.first_element && second_element == other.second_element;
	}

	bool operator!=(const pair &other) {
		return !(*this == other);
	}
	
	bool operator<(const pair &other) {
		return first_element < other.first_element || (first_element == other.first_element && second_element < other.second_element);
	}

	bool operator>(const pair &other) {
		return other < *this;
	}
};
