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
#define INT_MAX 2147483647
#define MIN(A, B) (A > B ? B : A)

int ShortestFullPath(int roads[N][N]);

// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    PrintRoadsInputMessage();
    int roads[N][N];
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            scanf("%d", &roads[row][col]);
        }
    }
    PrintLenOfShortestFullPath(ShortestFullPath(roads));
    return 0;
}

void tsp(roads, visited, current_city, visited_city_count, cost_till_now, min_distance)
    int roads[N][N];
    bool visited[N];
    int current_city;
    int visited_city_count;
    int cost_till_now;
    int *min_distance;
{
    if (visited_city_count == N - 1 && roads[current_city][0] > 0) {
        *min_distance =  MIN(*min_distance, (cost_till_now + roads[current_city][0]));
    }

    for (int next_city = 1; next_city < N; ++next_city) {
        int next_distance = roads[current_city][next_city];
        if (visited[next_city] == false && next_distance > 0) {
            visited[next_city] = true;
            tsp(roads, visited, next_city, visited_city_count + 1,
                cost_till_now + next_distance, min_distance);
            visited[next_city] = false;
        }
    }
}

// visit all cities and look for shortest path based on roads
int ShortestFullPath(int roads[N][N]) {
    bool visited[N] = {false};
    int min_distance = INT_MAX;
    tsp(roads, visited, 0, 0, 0, &min_distance);
    if (min_distance == INT_MAX) {
        return NO_PATH;
    }
    return min_distance;
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
