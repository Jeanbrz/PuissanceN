#include <stdio.h>

int initDataTable(int N_COLS, int* table_donnees);

void loadDataTable(int N_COLS, int* table_donnees, FILE* lastGame);

void loadVariables(long position, FILE* lastGame, int * variable);
