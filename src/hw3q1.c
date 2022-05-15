#include <stdio.h>
#define BSIZE 10
#define SHIP_AMOUNT 4
#define SHIP_A 3
#define SHIP_B 3
#define SHIP_C 4
#define SHIP_D 5

int rand_range(int low, int high) { // RAND_MAX assumed to be 32767
    static unsigned int next = 1;
    next = next * 1103515245 + 12345;
    return ((unsigned int)(next/65536) % 32768) % (high - low + 1) + low;
}

void srand_range(unsigned int seed) {
    for (int i = 0; (unsigned int)i < seed; i++) {
        rand_range(i, i + 1);
    }
}

void print_player_board(char board[BSIZE][BSIZE]) {
    for (int row = BSIZE - 1; row >= 0; --row) {
        printf("%d |", row);
        for (int col = 0; col < BSIZE; ++col) {
            if (board[row][col] >= '0' && board[row][col] <= '9') {
                printf(" *");
            } else {
                printf(" %c", board[row][col]);
            }
        }
        printf("\n");
    }

    printf("    - - - - - - - - - -\n   ");
    for (int col = 0; col < BSIZE; ++col) {
        printf(" %d", col);
    }
    printf("\n");
}

void print_cpu_board(char board[BSIZE][BSIZE]) {
    for (int row = BSIZE - 1; row >= 0; --row) {
        printf("%d |", row);
        for (int col = 0; col < BSIZE; ++col) {
            if (board[row][col] >= '0' && board[row][col] <= '9') {
                printf("  ");
            } else {
                printf(" %c", board[row][col]);
            }
        }
        printf("\n");
    }

    printf("    - - - - - - - - - -\n   ");
    for (int col = 0; col < BSIZE; ++col) {
        printf(" %d", col);
    }
    printf("\n");
}

unsigned int init_game() {
    printf("Welcome to Battleship!\n");

    printf("Please enter seed:\n");
    unsigned int seed = 0;
    scanf("%u", &seed);
    srand_range(seed);

    unsigned int level;
    printf("Please enter level:\n");
    scanf("%u", &level);
    return level;
}

int get_ship_len(int id) {
    int lengths[SHIP_AMOUNT] = {SHIP_A, SHIP_B, SHIP_C, SHIP_D};
    return lengths[id];
}

int is_direction_ok(int dir_x, int dir_y) {
    // both dir_x and dir_y are in range of [-1, 1]
    // but they cant be both 0 at the same time.
    if (dir_x < -1 || dir_x > 1) {
        return 0;
    }

    if (dir_y < -1 || dir_y > 1) {
        return 0;
    }

    if (dir_x == 0 && dir_y == 0) {
        return 0;
    }

    return 1;
}

int ship_clearance(board, x, y, dir_x, dir_y, ship_id)
    char board[BSIZE][BSIZE];
    int x;
    int y;
    int dir_x;
    int dir_y;
    int ship_id;
{
    if (is_direction_ok(dir_x, dir_y) == 0) {
        return 0;
    }

    int ship_len = get_ship_len(ship_id);
    // does ship fit in board?
    int y_bound = y + dir_y * (ship_len - 1);
    if (y_bound >= BSIZE || y_bound < 0 || y < 0 || y >= BSIZE) {
        return 0;
    }

    int x_bound = x + dir_x * (ship_len - 1);
    if (x_bound >= BSIZE || x_bound < 0 || x < 0 || x >= BSIZE) {
        return 0;
    }
    // check for ship clearence.
    for (int i = 0; i < ship_len; ++i) {
        if (board[y + dir_y * i][x + dir_x * i] != ' ') {
            return 0;
        }
    }

    return 1;
}

int place_ship(board, x, y, dir_x, dir_y, ship_id)
    char board[BSIZE][BSIZE];
    int x;
    int y;
    int dir_x;
    int dir_y;
    int ship_id;
{
    if (!ship_clearance(board, x, y, dir_x, dir_y, ship_id)) {
        return 0;
    } 

    for (int i = 0; i < get_ship_len(ship_id); ++i) {
        board[y + dir_y * i][x + dir_x * i] = ship_id + '0';
    }

    return 1;
}

int place_ship_user(char board[BSIZE][BSIZE], int ship_id) {
    int x, y, dir_x, dir_y;
    print_player_board(board);
    int ship_len = get_ship_len(ship_id);
    printf("Enter location for Battleship of size %d:\n", ship_len);
    if (scanf("%d,%d %d,%d", &x, &y, &dir_x, &dir_y) < 4) {
        return 0;
    }
    while (place_ship(board, x, y, dir_x, dir_y, ship_id) != 1) {
        printf("Error: Incorrect parameters!"
                " Please enter location "
                "for the Battleship size %d again:\n", ship_len);
        if (scanf("%d,%d %d,%d", &x, &y, &dir_x, &dir_y) < 4) {
            return 0;
        }
    }
    return 1;
}

void place_ship_cpu(char board[BSIZE][BSIZE], int ship_id) {
    int x, y, dir_x, dir_y;
    do {
        x = rand_range(0, 9);
        y = rand_range(0, 9);
        dir_x = rand_range(-1, 1);
        dir_y = rand_range(-1, 1);
    } while (!place_ship(board, x, y, dir_x, dir_y, ship_id));
}

void init_board(char board[BSIZE][BSIZE]) {
    for (int row = 0; row < BSIZE; ++row) {
        for (int col = 0; col < BSIZE; ++col) {
            board[row][col] = ' ';
        }
    }
}

void init_board_cpu(char board[BSIZE][BSIZE]) {
    init_board(board);
    for (int id = 0; id < SHIP_AMOUNT; ++id) {
        place_ship_cpu(board, id);
    }
}

int init_board_user(char board[BSIZE][BSIZE]) {
    init_board(board);
    for (int id = 0; id < SHIP_AMOUNT; ++id) {
        if (!place_ship_user(board, id)) {
            return 0;
        }

    }
    printf("All battleships have been located successfully!\n");
    return 1;
}

int attack_board(board, histogram, x, y)
    char board[BSIZE][BSIZE];
    int histogram[SHIP_AMOUNT];
    int x;
    int y;
{
    if (x < 0 || x >= BSIZE || y < 0 || y >= BSIZE) {
        return 0;
    }

    char target = board[y][x];
    if (target == 'V' || target == 'X') {
        return 0;
    }

    if (target == ' ') {
        board[y][x] = 'X';
        return 1;
    }

    histogram[target - '0'] += 1;
    board[y][x] = 'V';
    return 1;
}

void check_ships_user(int histogram[SHIP_AMOUNT]) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        int len = get_ship_len(i);
        if (histogram[i] == len) {
            printf("Your battleship of size %d has been drowned!\n", len);
            // make sure we never print this ship again
            histogram[i] += 1;
        }
    }
}

void check_ships_cpu(int histogram[SHIP_AMOUNT]) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        int len = get_ship_len(i);
        if (histogram[i] == len) {
            printf("The computer's battleship of size"
                   " %d has been drowned!\n", len);
            // make sure we never print this ship again
            histogram[i] += 1;
        }
    }
}

void prompt_attack_user(p_board, cpu_board)
    char p_board[BSIZE][BSIZE];
    char cpu_board[BSIZE][BSIZE];
{
    printf("Your following table:\n");
    print_cpu_board(cpu_board);
    printf("The computer's following table:\n");
    print_player_board(p_board);
    printf("It's your turn!\n"
           "Enter coordinates for attack:\n");
}


int attack_board_user(p_board, cpu_board, histogram)
    char p_board[BSIZE][BSIZE];
    char cpu_board[BSIZE][BSIZE];
    int histogram[SHIP_AMOUNT];
{
    prompt_attack_user(p_board, cpu_board);
    int x = 0, y = 0;
    if (scanf("%d,%d", &x, &y) < 2) {
        return 0;
    }
    int attack_result = attack_board(cpu_board, histogram, x, y);
    while (attack_result == 0) {
        printf("Error: Incorrect parameters! "
                "Please enter coordinates for attack again:\n");
        if (scanf("%d,%d", &x, &y) < 2) {
            return 0;
        }
        attack_result = attack_board(cpu_board, histogram, x, y);
    }
    check_ships_cpu(histogram);
    return 1;
}

void attack_board_cpu(p_board, histogram, level)
    char p_board[BSIZE][BSIZE];
    int histogram[SHIP_AMOUNT];
    int level;
{
    int attack_result = 0, x = 0, y = 0;
    for (int i = 0; i < level; ++i) {
        do {
            x = rand_range(0, 9);
            y = rand_range(0, 9);
            attack_result = attack_board(p_board, histogram, x, y);
        } while (attack_result == 0);
        check_ships_user(histogram);
    }
}

int check_win_cpu(int p_histogram[SHIP_AMOUNT]) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        if (p_histogram[i] <= get_ship_len(i)) {
            return 0;
        }
    }
    return 1;
}

int check_win_user(int cpu_histogram[SHIP_AMOUNT]) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        if (cpu_histogram[i] <= get_ship_len(i)) {
            return 0;
        }
    }
    return 1;
}

int loop(p_board, cpu_board, p_histogram, cpu_histogram, level)
    char p_board[BSIZE][BSIZE];
    char cpu_board[BSIZE][BSIZE];
    int p_histogram[SHIP_AMOUNT];
    int cpu_histogram[SHIP_AMOUNT];
    int level;
{
    while (1) {
        if (attack_board_user(p_board, cpu_board, cpu_histogram) == 0) {
            printf("Error: Invalid input!\n");
            return 0;
        }
        attack_board_cpu(p_board, p_histogram, level);
        if (check_win_cpu(p_histogram)) {
            printf("Game over! You lost...\n");
            return 0;
        }
        if (check_win_user(cpu_histogram)) {
            printf("Congrats! You are the winner!\n");
            return 0;
        }
    }
}

int main() {
    unsigned int level = init_game();
    char p_board[BSIZE][BSIZE]; // players data table
    char cpu_board[BSIZE][BSIZE]; // cpus data table
    int p_histogram[SHIP_AMOUNT] = {0};
    int cpu_histogram[SHIP_AMOUNT] = {0};
    if (init_board_user(p_board) == 0) {
        printf("Error: Invalid input!\n");
        return 0;
    }
    init_board_cpu(cpu_board);
    return loop(p_board, cpu_board, p_histogram, cpu_histogram, level);
}
