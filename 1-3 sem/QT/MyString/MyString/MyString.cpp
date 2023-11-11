#include "pch.h" 
#include <utility>
#include <limits.h>
#include "mystring.h"

MyString::MyString() {
	length = 0;
	str = new char[1];
	str[0] = '\0';
}

MyString::MyString(const char* s) {
	str = new char[strlen(s) + 1];
	strcpy(str, s);
}

MyString::MyString(const char* s, int n) {
	str = new char[n + 1];
	strncpy(str, s, n);
	str[n] = '\0';
}

MyString::~MyString() {
	
}

void* MyString::memcpy(void* s1, const void* s2, size_t n) {
	char* p1 = (char*)s1;
	const char* p2 = (const char*)s2;
	for (size_t i = 0; i < n; i++) {
		p1[i] = p2[i];
	}
	return s1;
}

void* MyString::memmove(void* s1, const void* s2, size_t n) {
	char* p1 = (char*)s1;
	const char* p2 = (const char*)s2;
	if (p1 < p2) {
		for (size_t i = 0; i < n; i++) {
			p1[i] = p2[i];
		}
	}
	else {
		for (size_t i = n - 1; i >= 0; i--) {
			p1[i] = p2[i];
		}
	}
	return s1;
}

char* MyString::strcpy(char* s1, const char* s2) {
	char* p1 = s1;
	const char* p2 = s2;
	while (*p2 != '\0') {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

char* MyString:: strncpy(char* s1, const char* s2, size_t n) {
	char* p1 = s1;
	const char* p2 = s2;
	for (size_t i = 0; i < n; i++) {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

///////////stronge things
char* MyString::strcat(char* s1, const char* s2) {
	char* p1 = s1;
	const char* p2 = s2;
	while (*p1 != '\0') {
		p1++;
	}
	while (*p2 != '\0') {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

char* MyString::strncat(char* s1, const char* s2, size_t n) {
	char* p1 = s1;
	const char* p2 = s2;
	while (*p1 != '\0') {
		p1++;
	}
	for (size_t i = 0; i < n; i++) {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

int MyString::memcmp(const void* s1, const void* s2, size_t n) {
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;
	for (size_t i = 0; i < n; i++) {
		if (p1[i] < p2[i]) {
			return -1;
		}
		else if (p1[i] > p2[i]) {
			return 1;
		}
	}
	return 0;
}

int MyString::strcmp(const char* s1, const char* s2) {
	const char* p1 = s1;
	const char* p2 = s2;
	while (*p1 != '\0' && *p2 != '\0') {
		if (*p1 < *p2) {
			return -1;
		}
		else if (*p1 > *p2) {
			return 1;
		}
		p1++;
		p2++;
	}
	if (*p1 == '\0' && *p2 == '\0') {
		return 0;
	}
	else if (*p1 == '\0') {
		return -1;
	}
	else {
		return 1;
	}
}

int MyString::strcoll(const char* s1, const char* s2) {
	return strcmp(s1, s2);
}

int MyString::strncmp(const char* s1, const char* s2, size_t n) {
	const char* p1 = s1;
	const char* p2 = s2;
	for (size_t i = 0; i < n; i++) {
		if (p1[i] < p2[i]) {
			return -1;
		}
		else if (p1[i] > p2[i]) {
			return 1;
		}
	}
	if (n == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

size_t MyString::strxfrm(char* s1, const char* s2, size_t n) {
	char* p1 = s1;
	const char* p2 = s2;
	for (size_t i = 0; i < n; i++) {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return n;
}

char* MyString::strtok(char* s1, char d) {
	static char* input = nullptr;
	if (s1 != nullptr) {
		input = s1;
	}
	if (input == nullptr)
	{
		return nullptr;
	}
	char* result = new char[strlen(input) + 1];
	int i = 0;
	for (; input[i] != '\0'; i++)
	{
		if (input[i] != d)
		{
			result[i] = input[i];
		}
		else {
			result[i] = '\0';
			input = input + i + 1;
			return result;
		}
	}
	result[i] = '\0';
	input = nullptr;
	return result;
}

void* MyString::memset(void* s, int c, size_t n) {
	char* p = (char*)s;
	for (size_t i = 0; i < n; i++) {
		p[i] = c;
	}
	return s;
}


size_t MyString::strlen(const char* s) {
	size_t size = 0;
	while (s[size] != '\0') {
		size++;
	}
	return size;
}










