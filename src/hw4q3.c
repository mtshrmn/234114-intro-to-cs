// **************************************************************************************
//			SUPPLIED SECTION - DO NOT ALTER
// **************************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FAILURE -1
#define SUCCESS 0

#define Q1_SECTION_A 'a'
#define Q1_SECTION_B 'b'
#define Q1_SECTION_C 'c'
#define Q1_TIME 't'
#define Q1_SPACE 's'

char SectionATimeComplexity();
char SectionASpaceComplexity();
char SectionBTimeComplexity();
char SectionBSpaceComplexity();
char SectionCTimeComplexity();
char SectionCSpaceComplexity();

void PrintAnswer(char answer)
{
	printf("%c\n", answer);
}

int test()
{
	char section, time_or_space;
	if (scanf("%c %c", &section, &time_or_space) != 2)
		return FAILURE;

	switch (section)
	{
	case Q1_SECTION_A:
		PrintAnswer(time_or_space == 't' ? SectionATimeComplexity()
              : SectionASpaceComplexity());
		break;
	case Q1_SECTION_B:
		PrintAnswer(time_or_space == 't' ? SectionBTimeComplexity()
              : SectionBSpaceComplexity());
		break;

	case Q1_SECTION_C:
		PrintAnswer(time_or_space == 't' ? SectionCTimeComplexity()
              : SectionCSpaceComplexity());
		break;

	default:
		printf("Error!\n");
	}

	return SUCCESS;
}

int main()
{
    test();
	return 0;
}

// **************************************************************************************
//			END OF SUPPLIED SECTION
// **************************************************************************************

// **************************************************************************************
//
//							make changes here
//
// **************************************************************************************

// return the correct answer, 'a'-'z'
// use ONLY lower letter answers

char SectionATimeComplexity()
{
	return 'k';
}

char SectionASpaceComplexity()
{
	return 'a';
}

char SectionBTimeComplexity()
{
	return 'g';
}

char SectionBSpaceComplexity()
{
	return 'a';
}

char SectionCTimeComplexity()
{
	return 'e';
}

char SectionCSpaceComplexity()
{
	return 'g';
}



