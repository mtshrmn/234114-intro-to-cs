#include <stdio.h>
#define BSIZE 10
#define CPU 0
#define PLAYER 1
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

// the board stores the ships' id at their position.
// the id's are stored as the ascii values of the id.
// this means this design supports maximum of 10 ships.
// print_board replaces the ship ids with a given char `replace`.
void print_board(char board[BSIZE][BSIZE], char replace) {
    for (int row = BSIZE - 1; row >= 0; --row) {
        printf("%d |", row);
        for (int col = 0; col < BSIZE; ++col) {
            if (board[row][col] >= '0' && board[row][col] <= '9') {
                printf(" %c", replace);
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

// let the player see where his ships are located
// we replace the ship ids with a "*".
void print_player_board(char board[BSIZE][BSIZE]) {
    print_board(board, '*');
}

// the cpu board ships should stay hidden,
// replace the ids with a space.
void print_cpu_board(char board[BSIZE][BSIZE]) {
    print_board(board, ' ');
}

// initializes the game, runs the seed and returns the game level.
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

// because we work with ship ids and not their length,
// we need a function to retrieve a ships length by id.
int get_ship_len(int id) {
    int lengths[SHIP_AMOUNT] = {SHIP_A, SHIP_B, SHIP_C, SHIP_D};
    return lengths[id];
}

// checks if a given direction is valid
// let direction be (x,y). if |x| or |y| > 1, it's not ok.
// if x = y = 0, also not ok.
// everything else ok.
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

// checks if a ship can be place onto the board.
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
    // check if ships length fits onto board
    // y coordinate:
    int y_bound = y + dir_y * (ship_len - 1);
    if (y_bound >= BSIZE || y_bound < 0 || y < 0 || y >= BSIZE) {
        return 0;
    }

    // x coordinate:
    int x_bound = x + dir_x * (ship_len - 1);
    if (x_bound >= BSIZE || x_bound < 0 || x < 0 || x >= BSIZE) {
        return 0;
    }
    // we cannot overwrite an existing ship
    for (int i = 0; i < ship_len; ++i) {
        if (board[y + dir_y * i][x + dir_x * i] != ' ') {
            return 0;
        }
    }

    return 1;
}

// given position and direction, place a ship onto board
// returns the success of placement.
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

// handle the user's ship placement.
// returns 1 if placement was successful
// if the user's syntax is wrong, return 0.
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

// handle the cpu ship placement
// because the ship can't input wrong syntax,
// it doesn't need to be checked. so function returns void.
void place_ship_cpu(char board[BSIZE][BSIZE], int ship_id) {
    int x, y, dir_x, dir_y;
    do {
        x = rand_range(0, BSIZE - 1);
        y = rand_range(0, BSIZE - 1);
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

// places the ships of the cpu onto its board.
void init_board_cpu(char board[BSIZE][BSIZE]) {
    init_board(board);
    for (int id = 0; id < SHIP_AMOUNT; ++id) {
        place_ship_cpu(board, id);
    }
}

// prompt the user to place his ships onto the board.
// bubble the syntax error upward and return its status.
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

// checks if the player destroyed one of the oppnent's ships
// and print it's length
void check_ships(int histogram[SHIP_AMOUNT], int player) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        int len = get_ship_len(i);
        if (histogram[i] == len) {
            if (player == CPU) {
                printf("The computer's battleship of size"
                       " %d has been drowned!\n", len);
            } else if (player == PLAYER) {
                printf("Your battleship of size"
                       " %d has been drowned!\n", len);
            }
            // make sure we never print this ship again
            histogram[i] += 1;
        }
    }
}

// executes an attack at the specified coordinate.
// if attack was successful(regardless of result) - return 1.
// update the result on the board.
// otherwise return 0 (i.e. coordinates are invalid)
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

// because we have a limitation of 13 loc per function,
// this function simply prints the prompt, nothing else.
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

// prompts the user to attack the cpu.
// if the input syntax is incorrect, bubble error to main().
// otherwise keep asking for coordinates until a successful 
// attack is executed. then return 1.
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
    // checks if one of the cpu's ship was damaged.
    check_ships(histogram, CPU);
    return 1;
}

// the cpu will always enter a valid input, so no need to check.
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
        // check if one of the users ship was destroyed.
        check_ships(histogram, PLAYER);
    }
}

// checks if a given histogram indicates a win.
int check_win(int histogram[SHIP_AMOUNT]) {
    for (int i = 0; i < SHIP_AMOUNT; ++i) {
        if (histogram[i] <= get_ship_len(i)) {
            return 0;
        }
    }
    return 1;
}

// main game loop, will run forever
// until the user enters an invalid syntax.
// if he does, the function returns 0.
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
        if (check_win(p_histogram)) {
            printf("Game over! You lost...\n");
            return 0;
        }
        if (check_win(cpu_histogram)) {
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
