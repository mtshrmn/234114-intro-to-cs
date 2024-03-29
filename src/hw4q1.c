//#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N  500
#define CHAR_MAX 256
// make sure modulo returns non negative value.
#define MODULO(A, B) ((A % B + B) % B)
#define MAX(A, B) (A > B ? A : B)

//Include files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// function declerations
void PrintIDontKnow();
void PrintIKnow();
void test();
bool isPalindrome(char* str);
bool isMixedPalindrome(char* str);
bool isKCyclicPalindrome(char* str, int k);
int getLongestMixedSubstring(char* str);

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
	char str[N]={0};
    int k = 0;
    printf("Please enter your string and a non-negative integer...\n");
    if(scanf("%s%d", str, &k)!= 2 || k < 0)
        exit(1);

    if (isPalindrome(str)== true)
    {
        printf("Palindrome\n");
    }
    else
    {
        printf("Non-Palindrome\n");
    }

    if (isMixedPalindrome(str))
    {
       printf("Mixed Palindrome\n");

    }
    else
    {
        printf("Non-Mixed Palindrome\n");
    }


    if (isKCyclicPalindrome(str,k))
    {
       printf("%d-Cyclic Palindrome\n", k);

    }
    else
    {
        printf("Non-%d-Cyclic Palindrome\n", k);
    }

    int longest = getLongestMixedSubstring(str);
    printf("Longest mixed substring is:%d\n", longest);

}
void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}
void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}

bool isPalindrome(char* str) {
	int left = 0;
	int right = strlen(str) - 1;

	while (right > left) {
		if (str[left] != str[right]) {
			return false;
		}
		left++;
		right--;
	}
	return true;
}

bool isMixedPalindrome(char* str) {
	int char_num[CHAR_MAX] = {0};
	int odd_count = 0;
	// same as iterating until i < strlen(str).
	// directly checking != '\0' is faster.
	for (int i = 0; str[i] != '\0'; ++i) {
		char_num[(int) str[i]]++;
	}
	// check the amount of odd occurrences
	// if there's more than 1, it's not a mixed palindrome.
	for (int i = 0; i < CHAR_MAX; ++i) {
		if (char_num[i] % 2 == 1) {
			if (odd_count == 1) {
				return false;
			}
			odd_count++;
		}
	}
	return true;
}

bool isKCyclicPalindrome(char* str, int k) {
	int len = strlen(str);
	// rotating the string `len` times is equivalent to not rotating at all.
	// that way we make sure that len is always bigger than k.
	int modulo_k = MODULO(k, len);
	int left = modulo_k;
	int right = MODULO((modulo_k - 1), len);

	for (int i = 1; i < len / 2; ++i) {
		if (str[left] != str[right]) {
			return false;
		}
		left = MODULO((left + 1), len);
		right = MODULO((right - 1), len);
	}
	return true;
}

void reset_array(int arr[], int len) {
	for (int i = 0; i < len; ++i) {
		arr[i] = 0;
	}
}

int getLongestMixedSubstring(char* str) {
	int len = strlen(str);
	int occurrences[CHAR_MAX] = {0};
	int odd_count = 0;
	int max_len = 0;

	// we start from the beginning of the string, and go forwards.
	// inside the loop we will go backwards until we find a mixed-palindrome.
	for (int left = 0; left < len; ++left) {
		odd_count = 0;
		reset_array(occurrences, CHAR_MAX);

		// count all letters in str. I CANNOT BELIEVE IT'S HISTOGRAM.
		for (int right = left; right < len; ++right) {
			occurrences[(int) str[right]]++;
		}

		// calculate how many odd occurrences there are from `start` to real end.
		for (int i = 0; i < CHAR_MAX; ++i) {
			if (occurrences[i] % 2 == 1) {
				odd_count++;
			}
		}

		// each time, go back from the end and check if we have less than 2 odds.
		// if yes, it's a mixed palindrome, update the max palindrome if needed.
		// if no, update the occurrences and subtract from the odds if it's an odd.
		for (int right = len - 1; right >= left; --right) {
			if (odd_count <= 1) {
				max_len = MAX(max_len, (right - left + 1));
				// because we're moving backwards, the first time we get to this line-
				// we are guaranteed to get the biggest mixed-palindrome for the current `start`
				// so we can safely break and iterate over the next starting point.
				break;
			}
			int occurrence = occurrences[(int) str[right]];
			if (occurrence % 2 == 0 && occurrence > 1) {
				odd_count++;
			}
			if (occurrence % 2 == 1) {
				odd_count--;
			}
			// faster than "occurrences[...]--" because we don't apply optimizations in our code.
			occurrences[(int) str[right]] = occurrence - 1;
		}
	}
  return max_len;
}

