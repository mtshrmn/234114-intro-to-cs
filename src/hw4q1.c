//#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N  500


// ADD YOUR DEFINES HERE



//Include files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


//Function declarations ..
void PrintIDontKnow();
void PrintIKnow();
void test();

//Function declarations to be implemented by you :)
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



//Your code goes here .. ENJOY!!

bool isPalindrome(char* str)
{

   //TODO..ADD your code here. Feel free to change the return statement bellow.
    return true;
}



bool isMixedPalindrome(char* str)
{

    //TODO..ADD your code here. Feel free to change the return statement bellow.
    return true;

}


bool isKCyclicPalindrome(char* str, int k)
{
   //TODO..ADD your code here. Feel free to change the return statement bellow.
    return true;
}


int getLongestMixedSubstring(char* str)
{
    //TODO..ADD your code here. Feel free to change the return statement bellow.
    return 0;
}
