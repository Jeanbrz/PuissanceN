#include <stdio.h>
int initUserInterface();

void playGame(int gameMode, FILE* lastgame);

int getCellWidth(int N);

int getFirstPlayer();

int getNextPlayer(int currentPlayer);

void displayGrid(int N, int *grid, int cellWidth, int turn);
