#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRINGIFY(x) #x
#define MACRO(x)     STRINGIFY(x)

#define ROWS 3
#define COLS 3

char *readIn() {
    char *line = NULL;
    size_t size;
    if (getline(&line, &size, stdin) != -1) {
        return line;
    }
    return "";
}

int ReadInt() {
    return atoi(readIn());
}

struct GameState {
    int turn;
    int active;
    int board[ROWS][COLS];
};

int ClearBoard(struct GameState state) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t v = 0; v < COLS; v++) {
            state.board[i][v] = 0;
        }
    }
    return 0;
}

int DrawBoard(struct GameState state) {
    printf("\n\n=====================\n\n");
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS; k++) {
            char v[16];
            if (state.board[i][k] == 0) {
                sprintf(v, "(%i,%i)", i, k);
            } else if (state.board[i][k] == 1) {
                sprintf(v, " [X] ");
            } else if (state.board[i][k] == 2) {
                sprintf(v, " [O] ");
            } else {
                sprintf(v, " [!] ");
            }
            printf("%s", v);
            if (k == 2 && i < 2) {
                printf("\n------+-------+------\n");
            }
            if (k < 2) {
                printf(" | ");
            }
        }
    }
    printf("\n\n=====================\n\n");
    return 0;
}

int checkWin(struct GameState state) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t k = 0; k < COLS; k++) {
            int p = state.board[i][k];
            if (p != 0) {
                if (k == 1 && state.board[i][k-1] == p && state.board[i][k+1] == p) { // Left & Right
                    state.active = 0;
                    //printf("X: %i, Y: %i, M: LR", i, k);
                    return 1;
                } else if (i == 1 && state.board[i-1][k] == p && state.board[i+1][k] == p) { // Top & Bottom
                    state.active = 0;
                    //printf("X: %i, Y: %i, M: TB", i, k);
                    return 1;
                } else if (i == 1 && k == 1 && state.board[i-1][k-1] == p && state.board[i+1][k+1] == p) { // Top Left & Bottom Right
                    state.active = 0;
                    //printf("X: %i, Y: %i, M: TLBR", i, k);
                    return 1;
                } else if (i == 1 && k == 1 && state.board[i-1][k+1] == p && state.board[i+1][k-1] == p) { // Top Right & Bottom Left
                    state.active = 0;
                    //printf("X: %i, Y: %i, M: TRBL", i, k);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int checkDraw(struct GameState state) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t k = 0; k < COLS; k++) {
            if (state.board[i][k] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
    printf("+--------------------+\n| Build ID: %s |\n+--------------------+\n\n", MACRO(BUILDID));
    #endif

    struct GameState state;

    srand(time(NULL));

    state.active = 1;
    state.turn = 1;
    ClearBoard(state);

    while (state.active == 1) {
        DrawBoard(state);
        if (checkWin(state)) {
            if (((state.turn + 1) % 2) == 1) {
                printf("Winner is X!\n");
            } else {
                printf("Winner is O!\n");
            }
            break;
        } else if (checkDraw(state)) {
            printf("Draw!\n");
            break;
        } else if (state.turn == 1) {
            printf("Select X: ");
            int x = ReadInt();
            printf("Select Y: ");
            int y = ReadInt();
            //printf("(%i, %i)\n", x, y);
            if ((0 <= x && x <= 2) && (0 <= y && y <= 2)) {
                if (state.board[x][y] != 0) {
                    printf("Coordinate Taken\n");
                } else {
                    state.board[x][y] = 1;
                    state.turn = 0;
                }
            } else {
                printf("Invalid Coordinates\n");
            }
        } else if (state.turn == 0) {
            if (state.board[0][0] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[0][0] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[0][2] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[0][2] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[2][0] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[2][0] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[2][2] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[2][2] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[1][1] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[1][1] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[0][1] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[0][1] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[1][0] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[1][0] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[1][2] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[1][2] = 2;
                    state.turn = 1;
                }
            }
            if (state.board[2][1] == 0 && state.turn == 0) {
                if ((rand() % 2) == 1) {
                    state.board[2][1] = 2;
                    state.turn = 1;
                }
            }
        }
    }

    return 0;
}
