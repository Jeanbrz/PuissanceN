#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../AFFICHAGE/Affichage.h"
#include "../AFFICHAGE/userInput.h"
#include "Logique.h"

bool play(int currentPlayer, int N_COLS, int *grid) {

    int j, choice;

    printf("Joueur %d a vous de jouer\n", currentPlayer);
    choice = gameChoice();

    if (choice==1) {
        j = columnChoice(N_COLS);
        addValue(j, N_COLS, grid, currentPlayer);
    }
    if (choice==2){
        j = columnChoice(N_COLS);
        deleteValue(j, N_COLS, grid, currentPlayer);
    }
    return false;
}


int addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer) {

    int i = N_COLS - 1, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpdate + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell != 0) {

        if ((i == 0) && (currentCell != 0)) {

            printf("veuillez resaisir une colonne\n");
            j = columnChoice(N_COLS);
            i =  N_COLS;
        }
        i = i - 1;

        currentCellAdress = gridToUpdate + i * N_COLS + j;
        currentCell = *(currentCellAdress);
    }

    *(currentCellAdress) = currentPlayer;
    displayGrid(N_COLS, gridToUpdate, 2);

    return 0;
}

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer) {

    int i = 0, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpDown + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell!=getNextPlayer(currentPlayer)) {

        while (currentCell == 0) {

            if (i == N_COLS-1 ) {

                printf("veuillez resaisir une colonne\n");
                j = columnChoice(N_COLS);
                i = N_COLS - 2;
            }

            i = i + 1;
            currentCellAdress = gridToUpDown + i * N_COLS + j;
            currentCell = *(currentCellAdress);
        }

        currentCellAdress = gridToUpDown + i * N_COLS + j;
        currentCell = *(currentCellAdress);

            if (currentCell == currentPlayer) {

                printf("vous ne pouvez pas enlever votre propre jeton, veuillez resaisir une colonne valable\n");
                j = columnChoice(N_COLS);

            }

    }

    *(currentCellAdress) = 0;
    displayGrid(N_COLS, gridToUpDown, 2);

return 0;

}

