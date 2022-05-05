#pragma once


#ifdef MYSTRING_EXPORTS
#define MYSTRING_API __declspec(dllexport)
#else
#define MYSTRING_API __declspec(dllimport)
#endif

class MYSTRING_API MyString {
private:
	char* str;
	int length = 0;
public:
	MyString();
	MyString(const char* s);
	MyString(const char* s, int n);
	~MyString();
	void* memcpy(void* s1, const void* s2, size_t n);
	void* memmove(void* s1, const void* s2, size_t n);
	char* strcpy(char* s1, const char* s2);
	char* strncpy(char* s1, const char* s2, size_t n);
	char* strcat(char* s1, const char* s2);
	char* strncat(char* s1, const char* s2, size_t n);
	int memcmp(const void* s1, const void* s2, size_t n);
	int strcmp(const char* s1, const char* s2);
	int strcoll(const char* s1, const char* s2);
	int strncmp(const char* s1, const char* s2, size_t n);
	size_t strxfrm(char* s1, const char* s2, size_t n);
	char* strtok(char* s1, char d);
	void* memset(void* s, int c, size_t n);
	size_t strlen(const char* s);
};