#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define I_KNOW 1
#define I_DONT_KNOW 0


#define N (100)
#define MAX_LEN (255)
#define MAX_SENTENCE_LEN ((MAX_LEN + 1) * N - 1)
#define WORD_SEPERATOR ('_')
#define SUCCESS (0)
#define ERROR (1)
#define LOWER(C) ((C >= 'A' && C <= 'Z') ? C + 'a' - 'A' : C)

void PrintIDontKnow();
void PrintIKnow();
int test();
bool read_number_of_strings(int * n) ;


void free_strings(char * strings[], int n);
bool read_strings(char * strings[], int n);
bool are_sorted(char * strings[], int n);
bool is_string_in_array(char * strings[], int n, char * string);
void delete_words(char * words[], int n, char * sentence);

int main()
{
	// If you don't know uncomment next line
	// PrintIDontKnow();
	PrintIKnow();
	test();
	return 0;
}

void PrintIDontKnow()
{
	printf("%d\n", I_DONT_KNOW);
}

void PrintIKnow()
{
	printf("%d\n", I_KNOW);
}

bool read_number_of_strings(int * n) {
  if (scanf("%d", n) != 1) {
    return false;
  }

  return ((*n >= 1) && (*n <= N));
}

int test() {
  int n;
  printf("Enter number of banned words: \n");
  if (!read_number_of_strings(&n)) {
    printf("Invalid number!\n");
    return ERROR;
  }

  char * banned_words[N];
  printf("Enter banned words: \n");
  if (!read_strings(banned_words, n)) {
    printf("Can't read words!\n");
    return ERROR;
  }

  if (!are_sorted(banned_words, n)) {
    printf("Words are not sorted correctly!\n");
    free_strings(banned_words, n);
    return ERROR;
  }

  char sentence[MAX_SENTENCE_LEN + 1];
  printf("Enter a sentence:\n");
  if (scanf("%s", sentence) != 1) {
    printf("Invalid sentence!\n");
    free_strings(banned_words, n);
    return ERROR;
  }

  delete_words(banned_words, n, sentence);
  printf("Censored sentence:\n%s\n", sentence);

  free_strings(banned_words, n);
  return SUCCESS;
}

void free_strings(char * strings[], int n) {
	for (int i = 0; i < n; ++i) {
		free(strings[i]);
	}
}

bool read_strings(char * strings[], int n) {
	char *tmp_str = malloc((MAX_LEN + 1) * sizeof(char));
	for (int i = 0; i < n; ++i) {
		if (scanf("%s", tmp_str) != 1) {
			free_strings(strings, i);
			free(tmp_str);
			return false;
		}
		int len = strlen(tmp_str);
		char *str = malloc((len + 1) * sizeof(char));
		// str[len] = 0; // why?
		strcpy(str, tmp_str);
		strings[i] = str;
	}
	free(tmp_str);
	return true;
}

int strcmp_i(char *s1, char *s2) { // case insensitive comparison
	while (*s1 && *s2 && LOWER(*s1) == LOWER(*s2)) {
		s1++;
		s2++;
	}
	return LOWER(*s1) - LOWER(*s2);
}

bool are_sorted(char * strings[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		if (strcmp_i(strings[i], strings[i+1]) > 0) {
			return false;
		}
	}
	return true;
}

bool is_string_in_array(char * strings[], int n, char * string) {
	int left = 0;
	int right = n - 1;
	while (right >= left) {
		int mid = left + (right - left) / 2;
		int order = strcmp_i(string, strings[mid]);
		if (order == 0) {
			return true;
		}
		if (order > 0) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return false;
}

void delete_words(char * words[], int n, char * sentence) {
	int sentence_len = strlen(sentence);
	int word_idx = 0;
	char word[MAX_SENTENCE_LEN] = {0};
	char *tmp_sentence = malloc((sentence_len + 1)* sizeof(char));
	// reset tmp_sentence
	for (int i = 0; i <= sentence_len; ++i) {
		tmp_sentence[i] = 0;
	}

	for (int sentence_idx = 0; sentence_idx <= sentence_len; ++sentence_idx) {
		if (sentence[sentence_idx] == '_' || sentence_idx == sentence_len) {
			word[word_idx] = 0;
			if (!is_string_in_array(words, n, word)) {
				strcpy(tmp_sentence + strlen(tmp_sentence), "_");
				strcpy(tmp_sentence + strlen(tmp_sentence), word);
			}
			// next word please!
			for (int i = 0; i <= word_idx; ++i) {
				word[i] = 0;
			}
			word_idx = 0;
		} else {
			word[word_idx] = sentence[sentence_idx];
			word_idx++;
		}
	}
	strcpy(sentence, tmp_sentence + 1);
	free(tmp_sentence);
}

