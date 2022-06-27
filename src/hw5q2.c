/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/
/* put your #defines here*/

// declarations
bool isPalindrome(unsigned int x);
int represent(unsigned int x);
void sort_arr(unsigned int *arr, int len);

// Print functions declarations
void printArr(unsigned int arr[], int size);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main() {
    int len;
    scanf("%d", &len);

    unsigned int *arr = malloc(sizeof(unsigned int) * len);
    if (arr == NULL) {
        return 0;
    }
    for (int i = 0; i < len; ++i) {
        scanf("%u", arr + i);
    }
    sort_arr(arr, len);
    printArr(arr, len);
    return 0;
}

unsigned int reverse_int(unsigned int x, unsigned int partial) {
    if (x == 0) {
        return partial;
    }
    return reverse_int(x / 10, partial * 10 + x % 10);
}

bool isPalindrome(unsigned int x){
    return reverse_int(x, 0) == x;
}


int represent(unsigned int x){
    if (x <= 9) {
        return x;
    }
    unsigned int product = 1;
    while (x > 0) {
        product *= x % 10;
        x /= 10;
    }
    return represent(product);
}

int order(unsigned int a, unsigned int b) {
    int is_a_pal = isPalindrome(a);
    int is_b_pal = isPalindrome(b);
    if (is_a_pal != is_b_pal) {
        return is_a_pal - is_b_pal;
    }

    int represent_a = represent(a);
    int represent_b = represent(b);
    if (represent_b != represent_a) {
        return represent_b - represent_a;
    }

    if (b < a) {
        return -1;
    }
    return b - a;
}

void sort_arr(unsigned *arr, int len) {
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (order(arr[j-1], arr[j]) < 0) {
                // swap items
                unsigned int tmp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

// print function
void printArr(unsigned int arr[], int size){
    for(int i=0; i<size; i++) printf("%d\n",arr[i]);
}
