#include <stdio.h>
// entire hw is dependent on those constants,
// they never change and they add clutter
// M = 4, N = MAX_BYTE_VALUE = M * M;
#define M 4
#define N 16 
#define MAX_BYTE_VALUE 16

// PLEASE READ THIS ==========================
// you asked for explanation of each function.
// be ready for some redundant comments.
// ===========================================

// applies a lookup table on a block
void map_block(int block[M][M], int lut[N]) {
  for (int i = 0; i < N; ++i) {
    int row = i / M;
    int col = i % M;
    block[row][col] = lut[block[row][col]];
  }
}

// shifts a row to the left once.
void shift_row_once(int row[M]) {
  int first_element = row[0];
  for (int i = 0; i < M; ++i) {
    row[i] = row[(i + 1) % M];
  }
  row[M - 1] = first_element;
}

// shifts a row to the left by specified steps.
void shift_row(int row[M], int step) {
  for (int i = 0; i < step; i++) {
    shift_row_once(row);
  }
}

// shifts a block,
// each row is shifted left by the row's index 
void shift_block(int block[M][M]) {
  for (int i = 0; i < M; i++) {
    shift_row(block[i], i);
  }
}

// modulu adds a key to the block.
void add_round_key(int block[M][M], int key[], int key_len) {
  for (int i = 0; i < N; ++i) {
    int row = i / M;
    int col = i % M;
    block[row][col] += key[i % key_len];
    block[row][col] %= MAX_BYTE_VALUE;
  }
}

/* copies a block of MxM from the entire message based on the offset
 * example where idx would be 1:
 *
 *         message:              chunk:
 * +---------+---------+      +---------+ 
 * |         |         |      |         |
 * |    A    |    B    | ---> |    B    |
 * |         |         |      |         |
 * |         |         |      |         |
 * +---------+---------+      +---------+
 */
void copy_chunk(int chunk[M][M], int message[M][N], int idx) {
  for (int i = 0; i < N; ++i) {
    int row = i / M;
    int col = i % M;
    chunk[row][col] = message[row][col + idx * M];
  }
}

/* does exactly what `copy_chunk` does but in reverse.
 * copies the block back into the message.
 * example where we embed index 0:
 *
 *         message:              chunk:
 * +---------+---------+      +---------+ 
 * |         |         |      |         |
 * |    A    |    B    | <--- |    A    |
 * |         |         |      |         |
 * |         |         |      |         |
 * +---------+---------+      +---------+
 */
void embed_chunk(int chunk[M][M], int message[M][N], int idx) {
  for (int i = 0; i < N; ++i) {
      int row = i / M;
      int col = i % M;
      message[row][col + idx * M] = chunk[row][col];
  }
}

// encrypts a single block
void aes_encrypt_block(chunk, lut, key, key_len)
  int chunk[M][M];
  int lut[N];
  int key[];
  int key_len;
{
  add_round_key(chunk, key, key_len);
  // total of ten rounds, but the first round is complete.
  for (int i = 0; i < 9; ++i) {
    map_block(chunk, lut);
    shift_block(chunk);
    add_round_key(chunk, key, key_len);
  }
}

// encrypts entire message
void aes_encrypt(message, lut, key, key_len, columns)
  int message[M][N];
  int lut[N];
  int key[];
  int key_len;
  int columns;
{
  for (int i = 0; i < columns / M; ++i) {
    int chunk[M][M] = {0};
    copy_chunk(chunk, message, i);
    aes_encrypt_block(chunk, lut, key, key_len);
    embed_chunk(chunk, message, i);
  }
}

// stores the key and returns key length
int get_key(int key[N]) {
  int key_len = 0;

  printf("Enter size of key:\n");
  scanf("%d", &key_len);

  printf("Enter the key:\n");
  for (int i = 0; i < key_len; ++i) {
    if (scanf("%d", &key[i]) < 1) {
      break;
    }
  }

  return key_len;
}

// stores the message and returns the number columns of the message
int get_message(int message[M][N]) {
  int columns = M;

  printf("Enter the number of columns of the message:\n");
  scanf("%d", &columns);

  printf("Enter the message you want to encrypt:\n");
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < columns; ++j) {
      scanf("%d", &message[i][j]);
    }
  }

  return columns;
}

// prints the message
void print_message(int message[M][N], int columns) {
  printf("Encrypted message:\n");
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < columns; ++j) {
      printf("%d ", message[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int map[MAX_BYTE_VALUE] = {10, 1, 2, 4, 7, 9, 14, 12,
                               3 ,5, 6, 13, 15, 11, 8, 0};
  int key[N] = {0}; // key cant be bigger than N.
  int message[M][N] = {{0}};
  int key_len = get_key(key);
  int columns = get_message(message);
  aes_encrypt(message, map, key, key_len, columns);
  print_message(message, columns);
  return 0;
}
