#include <stdio.h>

#define N 10 // number of digits in a decimal system
#define MAX(a, b) a > b ? a : b

/* 
 * Function: populate_info
 * -----------------------
 * populates an array with digit frequencies,
 * and calculates the amount of occurrences of each digit
 * before each other digit.
 * the function prints:
 *  - number of digits
 *  - longet digit subsequence
 *
 * d_frequency: array for digit frequencies
 * sequential:  array of occurrences
 *
 * returns: number of digits in the scanned sequence.
 */
int populate_info(int d_frequency[N], int sequential[N][N]) {
  // TODO: after assignment, decalre each variable in a seperate line.
  int d_amount = 0, d_combo = 0, d_combo_max = 0;
  char ch;

  printf("Enter a sequence of characters:\n");
  while (scanf("%c", &ch) != EOF) {
    if( ch >= '0' && ch <= '9' ) {
      d_amount++;
      for (int i = 0; i < N; ++i) {
        sequential[i][ch - '0'] += d_frequency[i];
      }
      d_frequency[ch - '0']++;
      d_combo++;
      d_combo_max = MAX(d_combo_max, d_combo);
    } else { // `ch` is not a digit
      d_combo = 0;
    }
  }
  printf("Number of digits: %d\n", d_amount);
  printf("Longest digit subsequence: %d\n", d_combo_max);
  return d_amount;
}

/*
 * Function: print_freqencies
 * --------------------------
 * prints the probabilities of each digit in the sequence.
 *
 * d_frequency: array of digit frequencies
 * d_amount:    total number of digits in the sequence
 */
void print_freqencies(int d_frequency[N], int d_amount) {
  printf("Frequencies: ");
  for (int i = 0; i < N; ++i) {
    printf("%.2f ", (double) d_frequency[i] / d_amount);
  }
  printf("\n");
}

/*
 * Function: print_sequential
 * --------------------------
 * prints each occurrence of the digits before another digit,
 * the function prints only non zero rows and cols.
 *
 * d_frequency: array of digit frequencies
 * sequential:  the occurrences data
 */
void print_sequential(int d_frequency[N], int sequential[N][N]) {
  printf("Sequential:\n ");
  // print header
  for (int i = 0; i < N; ++i) {
    if (d_frequency[i] != 0) {
      printf(" %d", i);
    }
  }

  printf("\n");

  for (int i = 0; i < N; ++i) {
    // dont print an empty row
    if (d_frequency[i] == 0) {
      continue;
    }

    printf("%d", i);
    // print the occurrences
    for (int j = 0; j < N; ++j) {
      if (d_frequency[j] != 0) {
        printf(" %d", sequential[i][j]);
      }
    }
    printf("\n");
  }
}

int main() {
  int d_frequency[N] = {0};
  int sequential[N][N] = {{0}};
  int d_amount = populate_info(d_frequency, sequential);
  print_freqencies(d_frequency, d_amount);
  print_sequential(d_frequency, sequential);
  return 0;
}
