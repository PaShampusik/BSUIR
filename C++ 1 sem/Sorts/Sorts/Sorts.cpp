#include<iostream>

using namespace std;

void ShakerSort(int n, int arr[]);
void SelectionSort(int n, int arr[]);
void InsertSort(int n, int arr[]);
void ShellSort(int n, int arr[]);
void BubleSort(int n, int arr[]);



void code(const char* str);
int main()
{
	
		std::cout << __cplusplus;
	
}


void code(const char* str)
{
	while (*str) {
		cout << (char)(*str + 1);
		str++;
	}
}

void BubleSort(int n, int arr[])
{
	int temp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void ShakerSort(int n, int arr[])
{
	bool swap = true;
	int buff = 0, left = 0, right = n - 1;
	while (swap && (left < right))
	{
		swap = false;
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				buff = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = buff;
				swap = true;
			}
		}
		right--;

		for (int i = right; i > left; i--)
		{
			if (arr[i - 1] > arr[i])
			{
				buff = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = buff;
				swap = true;
			}
		}
		left++;
	}
}

void SelectionSort(int n, int arr[])
{
	int min, temp;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

void InsertSort(int n, int arr[])
{
	int j, temp;
	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] <= temp)
			{
				break;
			}
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

void ShellSort(int n, int arr[])
{
	int i, j, temp;
	for (int step = n / 2; step > 0; step /= 2)
	{
		for (int i = step; i < n; i++)
		{
			temp = arr[i];
			for (j = i; j >= step; j -= step)
			{
				if (temp >= arr[j - step])
				{
					break;
				}
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
	}
}