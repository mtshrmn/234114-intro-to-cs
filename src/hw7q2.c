#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int  find_mistake(int dist[], int n); 
void PrintIDontKnow();
void PrintIKnow();
void test();

int main()
{
	// If you don't know uncomment next line
	// PrintIDontKnow();
	PrintIKnow();
	test();
	return 0;
}

void test()
{
	int arr[] = { 20,19,18,17,24,23,21,19,21 };
	int n = 9;
	printf("%d\n", find_mistake(arr, n));
}

int find_mistake(int dist[], int n)
{
	int right = n - 1;
	int left = 0;
	int mid = (right + left) / 2;
	while (right > left) {
		if (dist[left] >= dist[right]) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
		mid = (right + left) / 2;
	}
	return mid + 1;
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}
