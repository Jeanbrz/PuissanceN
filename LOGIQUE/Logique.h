#include <stdbool.h>
#include <stdio.h>

bool play(int currentPlayer, int N_COLS, int *grid, int turn, int gameMode, int *jNotAllowed);

bool addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer, int turn, int gameMode, int *jNotAllowed);

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer, int turn, int gameMode);

bool checkWin (int N, int j, int N_COLS, int *gridCheck, int currentPlayer);

void checkHorizontaly(int i, int j, int N_COLS, int *gridCheck, int currentPlayer, int *horizontalAdress, char direction[]);

void checkVertically(int i, int j, int N_COLS, int *gridCheck, int currentPlayer, int *belowAdress);

void checkDiagonal(int i,int j,int N_COLS,int *gridCheck,int currentPlayer, int *aboveAdress, char direction[]);

bool deleteAllowed(int N_COLS, int *gridCheck, int currentPlayer);

bool isDrawGame (int N_COLS, int *grid);