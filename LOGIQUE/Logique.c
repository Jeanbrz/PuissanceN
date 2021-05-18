#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Affichage.h"
#include "Logique.h"

bool play(int currentPlayer, int N, int grid[N+2][N+2]) {

    int j, choice;

    printf("Joueur %d a vous de jouer\n", currentPlayer);
    choice = gameChoice();
    if (choice==1) {
        j = columnChoice(N);
        addValue(j, N, grid, currentPlayer);
    }
    return false;
}


int addValue(int j, int N, int gridToUpdate[N+1][N+1], int currentPlayer) {

    int i=N+1;

    printf("N = %d, j = %d\n", N, j);
    while (gridToUpdate[i][j] != 0) {

        if ((i == 0) && (gridToUpdate[i][j] != 0)) {

            printf("veuillez resaisir une colonne\n");
            j = columnChoice(N);
            i = N+1;
        }
        i = i - 1;
    }
    gridToUpdate[i][j]= currentPlayer;
}
