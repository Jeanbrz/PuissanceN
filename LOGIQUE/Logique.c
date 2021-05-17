#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Affichage.h"
#include "Logique.h"

bool play(int currentPlayer, int N, int gridStatus[N+2][N+2]) {

    int j, choice;

    printf("Joueur %d a vous de jouer\n", currentPlayer);

    choice = gameChoice();

    switch (choice) {

        case 1:

            j = columnChoice(N);

            addValue(j, N, gridStatus, currentPlayer);

            break;


    }



}

int addValue(int j, int N, int gridStatus[N+2][N+2], int currentPlayer) {


    int i=N+2;

    while (gridStatus[i][j] != 0) {

        i = i - 1;

        if (i==0 && gridStatus[i][j] != 0) {

            printf("veuillez resaisir une colonne\n");
            j = columnChoice(N);
            i = N+2;
        }
    }
    gridStatus[i][j]= currentPlayer;

}
