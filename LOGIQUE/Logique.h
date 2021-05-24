#include <stdbool.h>

bool play(int currentPlayer, int N_COLS, int *grid, int turn, int gameMode);

int addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer, int turn, int gameMode);

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer, int turn, int gameMode);

int checkWin (int N, int j, int N_COLS, int *gridCheck, int currentPlayer);