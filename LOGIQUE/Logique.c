#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../AFFICHAGE/Affichage.h"
#include "../AFFICHAGE/userInput.h"
#include "Logique.h"

bool play(int currentPlayer, int N_COLS, int *grid, int turn, int gameMode) {

    int j, choice;

    if (gameMode == 1 && currentPlayer== 2) {
        printf("Ordinateur : \n");
    } else {
        printf("Joueur %d a vous de jouer\n", currentPlayer);
    }

    choice = gameChoice(turn, gameMode, currentPlayer);

    if (choice==1) {
        j = columnChoice(N_COLS, gameMode, currentPlayer);
        addValue(j, N_COLS, grid, currentPlayer, turn, gameMode);
    }
    if (choice==2){
        j = columnChoice(N_COLS, gameMode, currentPlayer);
        deleteValue(j, N_COLS, grid, currentPlayer, turn, gameMode);
    }
    return false;
}


int addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer, int turn, int gameMode) {

    int i = N_COLS - 1, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpdate + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell != 0) {

        if ((i == 0) && (currentCell != 0)) {

            printf("veuillez resaisir une colonne\n");
            j = columnChoice(N_COLS, gameMode, currentPlayer);
            i =  N_COLS;
        }
        i = i - 1;

        currentCellAdress = gridToUpdate + i * N_COLS + j;
        currentCell = *(currentCellAdress);
    }

    *(currentCellAdress) = currentPlayer;
    displayGrid(N_COLS, gridToUpdate, 2, turn);
    checkWin (i, j, N_COLS, gridToUpdate, currentPlayer);


    return 0;
}

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer, int turn, int gameMode) {

    int i = 0, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpDown + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell!=getNextPlayer(currentPlayer)) {

        while (currentCell == 0) {

            if (i == N_COLS-1 ) {

                printf("veuillez resaisir une colonne\n");
                j = columnChoice(N_COLS, gameMode, currentPlayer);
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
                j = columnChoice(N_COLS, gameMode,currentPlayer);

            }

    }

    *(currentCellAdress) = 0;
    displayGrid(N_COLS, gridToUpDown, 2, turn);


return 0;

}

int checkWin (int i, int j, int N_COLS, int *gridCheck, int currentPlayer) {

    int currentCell, *currentCellAdress, jCell=j+1, right = 0 , stock=j ;

    currentCellAdress = gridCheck + i * N_COLS + jCell;
    currentCell = *(currentCellAdress);

    while (currentCell == currentPlayer && jCell<N_COLS) {

        right = right + 1;
        jCell = jCell + 1;

        currentCellAdress = gridCheck + i * N_COLS + jCell;
        currentCell = *(currentCellAdress);
}
    printf("\n compteur joueur droite %d : %d \n", currentPlayer, right);

    int left=0;
    jCell=stock-1;

    currentCellAdress = gridCheck + i * N_COLS + jCell;
    currentCell = *(currentCellAdress);

    while (currentCell == currentPlayer && jCell>0) {

        left = left + 1;
        jCell = jCell - 1;

        currentCellAdress = gridCheck + i * N_COLS + jCell;
        currentCell = *(currentCellAdress);
    }

    printf("\n compteur joueur gauche %d : %d \n", currentPlayer, left);




}
