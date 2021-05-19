#include <stdbool.h>

bool play(int currentPlayer, int N_COLS, int *grid);

int addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer);

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer);