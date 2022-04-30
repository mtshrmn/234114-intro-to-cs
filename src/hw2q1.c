#include <stdio.h>

#define N 10
// you said no logic statements, bear the consequences
// NOTE: on x86, a ternary operation would be the fastest
#define MAX(a, b) ((a > b) * a + (a <= b) * b)
#define MIN(a, b) ((a < b) * a + (a >= b) * b)

// checkes if value in index `ind` is
// bigger than both neighboring values in seq.
int is_locally_max(int seq[N], int ind) {
  int val = seq[ind];
  // clamp neighbors to an actual value in the sequence
  int r_neighbor = seq[MIN((ind + 1), (N - 1))];
  int l_neighbor = seq[MAX((ind - 1), 0)];
  return val >= MAX(r_neighbor, l_neighbor);
}

// checks if value in even position is even
// or if value in odd position is odd.
int is_odd_even(int seq[N], int ind) {
  return seq[ind] % 2 == ind % 2;
}

int main() {
  int seq[N] = {0};
  int rank = 0;
  printf("Please enter a sequence:\n");
  for (int i = 0; i < 10; ++i) {
    // i trust the input
    scanf("%d", &seq[i]);
  }

  // could be faster than O(2n)
  for (int i = 0; i < 10; ++i) {
    rank += is_locally_max(seq, i) ^ is_odd_even(seq, i);
  }
  printf("Maximum-Parity degree: %d\n", rank);
  return 0;
}
