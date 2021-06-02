#include <stdio.h>
#include <stdbool.h>

int initUserInterface();

void playGame(bool isNewGame);

int getCellWidth(int N);

int getFirstPlayer();

int getNextPlayer(int currentPlayer);

void show_grid(int N, int *grid, int cellWidth, int turn);
