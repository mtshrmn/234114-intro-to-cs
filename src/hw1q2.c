#include <stdio.h>
#define UPERCASE_DELTA 'a' - 'A'

int main() {
  printf("Enter letter to count:\n");
  char letter;
  if (scanf("%c", &letter) == 0) {
    // theoretically, this should never happen.
    return 0;
  }
  if (letter > 'z' || letter < 'A') {
    return 0;
  }
  if (letter > 'Z' && letter < 'a') {
    // the lowercase and upercase letters have a gap. 
    return 0;
  }
  // we can assume that letter is of legal value.
  printf("Enter the char sequence:\n");
  char sequence_char;
  int occurrences_count = 0;
  while (scanf("%c", &sequence_char) == 1) {
    if (sequence_char == '#') {
      break;
    }
    // make sure letter is in upper case
    if (letter > 'Z') {
      letter -= UPERCASE_DELTA;
    }
    // case insensitive comparison.
    if (sequence_char == letter || sequence_char == letter + UPERCASE_DELTA) {
      occurrences_count++;
    }
  }
  printf("The letter appeared %d times\n", occurrences_count);
  return 0;
}
