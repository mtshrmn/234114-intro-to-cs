#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int  num_unbeatables(char* s);
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
	printf("%d\n", num_unbeatables("20AB5DcDabc67"));
	printf("%d\n", num_unbeatables("ABC123"));
}

int is_secure(char *s, int len) {
	// holds info about number of regex terms:
	// [numbers, lowercase, uppercase]
	int hist[3] = {0}; 
	for (int i = 0; i < len; ++i) {
		if (s[i] <= '9' && s[i] >= '0') {
			hist[0]++;
			continue;
		}

		if (s[i] <= 'z' && s[i] >= 'a') {
			hist[1]++;
			continue;
		}

		if (s[i] <= 'Z' && s[i] >= 'A') {
			hist[2]++;
		}
	}

	// check based on rules:
	// case one
	if (hist[0] == 1 && hist[1] == 4 && hist[2] == 1) {
		return 1;
	}
	// case 2
	if (hist[0] == 3 && hist[2] <= 3) {
		return 1;
	}
	return 0;
}


int num_unbeatables(char* s)
{		
	int count_secure = 0;
	int strlen = 0; //imagine using a variable that can be a function...
	for (; s[strlen] != 0; ++strlen){} // basically we implemented strlen()
	
	for (int start = 0; start < strlen; ++start) {
		for (int end = strlen; end > start; --end) {
			if (is_secure(s+start, end - start)) {
				count_secure++;
			}
		}
	}

	return count_secure;
}


void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}
