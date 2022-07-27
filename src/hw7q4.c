#define _CRT_SECURE_NO_WARNINGS

#define I_KNOW 1
#define I_DONT_KNOW 0
#define N 5
#define M 5

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_num_of_occurences(char letters[M][N], char* word);
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
	char letters[M][N] = { {'D', 'E', 'M', 'X', 'B'},
							{'A', 'O', 'E', 'P', 'E'},
							{'D', 'D', 'C', 'O', 'D'},
							{'E', 'B', 'E', 'D', 'S'},
							{'C', 'P', 'Y', 'E', 'N'} };
	char* word1 = "CODE";
	char* word2 = "YELL";
	printf("%d\n", find_num_of_occurences(letters, word1));
	printf("%d\n", find_num_of_occurences(letters, word2));
}

int find_num_of_occurences_aux(char letters[M][N], int last_x, int last_y, int so_far, char* word) {
	// implementation fo strlen()
	// of course i could optimize this code, but...
	int strlen = 0;
	for (; word[strlen] != 0; ++strlen){}
	if (so_far == strlen) {
		return 1;
	}

	int num_of_options = 0;

	for(int i = -1; i <= 1; ++i) {
		for(int j = -1; j <= 1; ++j) {
			// make sure we dont leave bounds
			if (last_x + i < 0 || last_x + i >= N) {
				continue;
			}
			if (last_y + j < 0 || last_y + j >= M) {
				continue;
			}

			if (letters[last_x+i][last_y+j] == word[so_far]) {
				letters[last_x+i][last_y+j] = 0;
				num_of_options += find_num_of_occurences_aux(letters, last_x + i, last_y + j, so_far + 1, word);
				letters[last_x+i][last_y+j] = word[so_far];
			}
		}
	}

	return num_of_options;
}

int find_num_of_occurences(char letters[M][N], char* word)
{
	// make sure word is not empty....
	int strlen = 0;
	for (; word[strlen] != 0; ++strlen){}
	if (strlen == 0) {
		return 1;
	}

	int sum_of_opts = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (letters[i][j] == word[0]) {
				sum_of_opts += find_num_of_occurences_aux(letters, i, j, 1, word);
			}
		}
	}
	return sum_of_opts;
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}

