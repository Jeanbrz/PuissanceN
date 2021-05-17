#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Affichage.h"

bool play(int currentPlayer, int N) {

    int grid[N+2][N+2];
    int i=N+2, j;

    printf("Joueur %d a vous de jouer\n", currentPlayer);

    j = columnChoice(N);


    if (grid[i][j] == 1 || grid[i][j] == 2) {
        while (grid[i][j] != 0) {
            i = i - 1;
        }
    }
    grid[i][j]= currentPlayer;
}
