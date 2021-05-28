#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../AFFICHAGE/Affichage.h"
#include "../AFFICHAGE/userInput.h"
#include "Logique.h"

bool play(int currentPlayer, int N_COLS, int *grid, int turn, int gameMode) {

    int j, choice;
    bool isGameOver = false;

    if (gameMode == 1 && currentPlayer== 2) {
        printf("Ordinateur : \n");
    } else {
        printf("Joueur %d a vous de jouer\n", currentPlayer);
    }
    if (deleteAllowed(N_COLS, grid, currentPlayer)==true){

        choice = gameChoice(turn, gameMode, currentPlayer, true);
    } else {
        choice = gameChoice(turn, gameMode, currentPlayer, false);
    }

    if (choice==1) {
        j = columnChoice(N_COLS, gameMode, currentPlayer);
        isGameOver = addValue(j, N_COLS, grid, currentPlayer, turn, gameMode);
    }
    if (choice==2){
        j = columnChoice(N_COLS, gameMode, currentPlayer);
        deleteValue(j, N_COLS, grid, currentPlayer, turn, gameMode);
    }
    return isGameOver;
}


bool addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer, int turn, int gameMode) {

    int i = N_COLS - 1, currentCell, *currentCellAdress;
    bool isWin;

    currentCellAdress = gridToUpdate + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell != 0) {

        if ((i == 0) && (currentCell != 0)) {

            if(gameMode==2 || currentPlayer==1){
                printf("veuillez resaisir une colonne\n");
            }
            j = columnChoice(N_COLS, gameMode, currentPlayer);
            i =  N_COLS;
        }
        i = i - 1;

        currentCellAdress = gridToUpdate + i * N_COLS + j;
        currentCell = *(currentCellAdress);
    }

    *(currentCellAdress) = currentPlayer;
    displayGrid(N_COLS, gridToUpdate, 2, turn);
    isWin = checkWin (i, j, N_COLS, gridToUpdate, currentPlayer);

    return isWin;
}

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer, int turn, int gameMode) {

    int i = 0, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpDown + i * N_COLS + j;
    currentCell = *(currentCellAdress);
    printf("currentPlayer : %d\n", currentPlayer);

    while (currentCell!=getNextPlayer(currentPlayer)) {

        printf("currentPlayer : %d\n", currentPlayer);

        while (currentCell == 0) {

            if (i == N_COLS-1 ) {

                if(gameMode==2 || currentPlayer == 1) {

                    printf("veuillez resaisir une colonne\n");
                }

                j = columnChoice(N_COLS, gameMode, currentPlayer);
                i = -1;

            }

            i = i + 1;
            currentCellAdress = gridToUpDown + i * N_COLS + j;
            currentCell = *(currentCellAdress);
        }

        currentCellAdress = gridToUpDown + i * N_COLS + j;
        currentCell = *(currentCellAdress);

        if (currentCell == currentPlayer) {
            if(gameMode==2 || currentPlayer == 1) {
                printf("Vous ne pouvez pas enlever votre propre jeton, veuillez resaisir une colonne valable\n");
            }

            j = columnChoice(N_COLS, gameMode,currentPlayer);

        }

    }

    *(currentCellAdress) = 0;
    displayGrid(N_COLS, gridToUpDown, 2, turn);


return 0;

}

bool checkWin (int i, int j, int N_COLS, int *gridCheck, int currentPlayer) {

    int right=0, left=0;
    int *rightAdress=&right, *leftAdress=&left;

    checkHorizontaly(i, j, N_COLS, gridCheck, currentPlayer, rightAdress, leftAdress);

    int  below=0;
    int *belowAdress=&below;
    checkVertically(i, j, N_COLS, gridCheck, currentPlayer, belowAdress);

     int aboveRight=0, aboveLeft=0;
     int *aboveRightAdress=&aboveRight, *aboveLeftAdress=&aboveLeft;

    checkDiagonal(i,j,N_COLS,gridCheck,currentPlayer, aboveRightAdress, "right");
    checkDiagonal(i,j,N_COLS,gridCheck,currentPlayer, aboveLeftAdress, "left");


    if (right+left+1>N_COLS-3 || below+1>N_COLS-3 || aboveRight>N_COLS-3 || aboveLeft>N_COLS-3) {

        printf("bravo joueur %d, vous avez win\n", currentPlayer);
        return true;

    }
    return false;
}


void checkHorizontaly(int i, int j, int N_COLS, int *gridCheck, int currentPlayer, int *rightAdress, int *leftAdress) {

    int currentCell, *currentCellAdress, jCell, stock = j, currentRight=*rightAdress, currentLeft=*leftAdress;

    jCell = j+1;

    currentCellAdress = gridCheck + i * N_COLS + jCell;
    currentCell = *(currentCellAdress);


    while (currentCell == currentPlayer && jCell < N_COLS+1) {

        currentRight = currentRight + 1;
        jCell = jCell + 1;

        currentCellAdress = gridCheck + i * N_COLS + jCell;
        currentCell = *(currentCellAdress);
    }


    jCell = stock - 1;

    currentCellAdress = gridCheck + i * N_COLS + jCell;
    currentCell = *(currentCellAdress);

    while (currentCell == currentPlayer && jCell > -1) {

        currentLeft = currentLeft + 1;
        jCell = jCell - 1;

        currentCellAdress = gridCheck + i * N_COLS + jCell;
        currentCell = *(currentCellAdress);
    }


    *leftAdress = currentLeft;
    *rightAdress = currentRight;

}

void checkVertically(int i, int j, int N_COLS, int *gridCheck, int currentPlayer, int *belowAdress) {

    int currentCell, *currentCellAdress, iCell, currentBelow=*belowAdress;

    iCell=i+1;

    currentCellAdress = gridCheck + iCell * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell==currentPlayer && iCell < N_COLS+1) {

        currentBelow = currentBelow + 1;
        iCell=iCell+1;

        currentCellAdress = gridCheck + iCell * N_COLS + j;
        currentCell = *(currentCellAdress);

    }


    *belowAdress=currentBelow;
}

 void checkDiagonal(int i,int j,int N_COLS,int *gridCheck,int currentPlayer, int *aboveAdress, char direction[]) {

    int iCell=i, jCell=j, currentCell, stockj=j, *currentCellAdress, currentAbove = *aboveAdress, jCellModif;


        if (strcmp(direction, "right")) {
        jCellModif=1;

        } else {

        jCellModif=-1;

        }


        while (iCell!=N_COLS-1 && jCell>=0 && jCell<=N_COLS-1) {
            iCell=iCell+1;
            jCell=jCell-jCellModif;
        }


        currentCellAdress = gridCheck + iCell * N_COLS + jCell;
        currentCell = *(currentCellAdress);

        while (currentAbove<N_COLS-2 && iCell>-1 && -1<jCell<N_COLS+1) {

            if (currentCell==currentPlayer) {

            currentAbove = currentAbove + 1;

             } else {
            currentAbove = 0;
             }

            iCell=iCell-1;
            jCell=jCell+jCellModif;

            currentCellAdress = gridCheck + iCell * N_COLS + jCell;
            currentCell = *(currentCellAdress);

        }

    *aboveAdress = currentAbove;
}

bool deleteAllowed(int N_COLS, int *gridCheck, int currentPlayer) {

    int i=0,j=0, currentCell, *currentCellAdress, compteur;

    currentCellAdress= gridCheck + i * N_COLS + j;
    currentCell=*(currentCellAdress);

    for (j=0; j<N_COLS+1; j++) {

        while (currentCell==0 && i<N_COLS+1){
            i = i-1;
            currentCellAdress= gridCheck + i * N_COLS + j;
            currentCell=*(currentCellAdress);

            if (i==N_COLS) {
                compteur = compteur + 1;
            }

        }

            if (currentCell==currentPlayer) {
            compteur = compteur + 1;

            } else {

            return false;
            }
    }

    if (compteur > 3){

        return true;

    } else {

        return false;
    }

}

