/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N 4
#define NO_ROAD -1
#define NO_PATH -1

int ShortestFullPath(int roads[N][N]);

// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    // implement
    return 0;
}

// visit all cities and look for shortest path based on roads
int ShortestFullPath(int roads[N][N]) {
    return 0;
}

// Print functions
void PrintLenOfShortestFullPath(int min_len)
{
    if(min_len == NO_PATH)
    {
        printf("There is no such path!\n");
    }
    else
    {
        printf("The shortest path is of length: %d\n", min_len);
    }
}

void PrintRoadsInputMessage()
{
    printf("Please enter the roads %dX%d matrix row by row:\n", N, N);
}
