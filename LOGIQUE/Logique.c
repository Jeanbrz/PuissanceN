#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../AFFICHAGE/Affichage.h"
#include "../AFFICHAGE/userInput.h"
#include "Logique.h"

/**
 * Fonction qui permet de gerer le bloc logique en appelant toutes les autres fonctions (addValue, deleteValue, Check, gameChoice, columnChoice).
 * @param N_COLS : la dimension de la grille (nbr jetons + 2)
 * @param currentPlayer : joueur actuel (il vaut soit 1 ou 2)
 * @param turn : variable qui compte le nombre de tour de la partie
 * @param gameMode : le menu de la partie
 * @return
 */

bool play(int currentPlayer, int N_COLS, int *grid, int turn, int gameMode, int *jNotAllowed) {

    int j, choice;
    bool isGameOver = false, isDeleteAllowed = false;

    FILE* lastGame=fopen("saveLastGame.txt", "w");

    if (gameMode == 1 && currentPlayer== 2) {
        printf("Ordinateur : \n");
    } else {
        printf("Joueur %d a vous de jouer\n", currentPlayer);
    }
    isDeleteAllowed = deleteAllowed(N_COLS, grid, currentPlayer);

    choice = gameChoice(gameMode, currentPlayer, isDeleteAllowed);

    switch (choice) {

        case 1:

            j = columnChoice(N_COLS, gameMode, currentPlayer);
            isGameOver = addValue(j, N_COLS, grid, currentPlayer, turn, gameMode, jNotAllowed);

            break;

        case 2 :

            j = columnChoice(N_COLS, gameMode, currentPlayer);
            *jNotAllowed = deleteValue(j, N_COLS, grid, currentPlayer, turn, gameMode);

            break;

        case 3 :


            fprintf(lastGame, "gameMode : %d\n", gameMode);
            fprintf(lastGame, "N_COLS : %d\n", N_COLS);
            fputs("gridStatus : ", lastGame);
            for (int i=0; i<N_COLS; i++) {

                for (j=0; j<N_COLS; j++){

                    int *currentCellAdress = grid + i * (N_COLS) + j;
                    fprintf(lastGame, "%d ", *(currentCellAdress));
                }
            }
            fprintf(lastGame, "\ncurrentPlayer : %d\n", currentPlayer);
            fprintf(lastGame, "turn : %d\n", turn);
            fclose(lastGame);
            isGameOver=true;

    }

    return isGameOver;
}

/**
 * On ajoute la valeur du joueur actuel (currentPlayer) dans le tableau tout en empechant qu'il ajoute sur une colonne pleine
 * @param j : le choix de colonne du joueur actuel
 * @param N_COLS : la dimension de la grille (nbr jetons + 2)
 * @param currentPlayer : joueur actuel (il vaut soit 1 ou 2)
 * @return
 */
bool addValue(int j, int N_COLS, int *gridToUpdate, int currentPlayer, int turn, int gameMode, int *jNotAllowed) {

    int i = N_COLS - 1, currentCell, *currentCellAdress;
    bool isWin;

    currentCellAdress = gridToUpdate + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell != 0 || j==*jNotAllowed) {

        if ((i == 0 && currentCell != 0) || j==*jNotAllowed) {

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
    *jNotAllowed=-1;

    return isWin;
}

/**
 * Dans cette fonction on enlève le pion de l'adversaire le plus haut dans la colonne choisie par le joueur actuel.
 * @param gridToUpDown : tableau du jeu où une valeur sera supprimée
 * @return
 */

int deleteValue(int j, int N_COLS, int *gridToUpDown, int currentPlayer, int turn, int gameMode) {

    int i = 0, currentCell, *currentCellAdress;

    currentCellAdress = gridToUpDown + i * N_COLS + j;
    currentCell = *(currentCellAdress);

    while (currentCell!=getNextPlayer(currentPlayer)) {

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

        if (currentCell == currentPlayer) {
            if(gameMode==2 || currentPlayer == 1) {
                printf("Vous ne pouvez pas enlever votre propre jeton, veuillez resaisir une colonne valable\n");
            }

            j = columnChoice(N_COLS, gameMode,currentPlayer);
            i=0;

        }
        currentCellAdress = gridToUpDown + i * N_COLS + j;
        currentCell = *(currentCellAdress);

    }

    *(currentCellAdress) = 0;
    displayGrid(N_COLS, gridToUpDown, 2, turn);


return j;

}
/**
 * Fonction booléenne qui appelle toutes les fonctions de Check (horizontale, verticale, diagonale)
   et qui verifie si le joueur a gagné (enchainement de N_COLS-2 même jetons). Si une des conditions de
   Check prouve que le joueur a gagné, la fonction renvoit 'true' pour arreter le programme.
 * @param i : la ligne du dernier pion ajouté
 * @param j : la colonne du dernier pion ajouté
 * @return
 */
bool checkWin (int i, int j, int N_COLS, int *gridCheck, int currentPlayer) {

    bool test;

    int right=0, left=0;
    int *rightAdress=&right, *leftAdress=&left;

    checkHorizontaly(i, j, N_COLS, gridCheck, currentPlayer, rightAdress, "right");
    checkHorizontaly(i, j, N_COLS, gridCheck, currentPlayer, leftAdress, "left");


    int  below=0;
    int *belowAdress=&below;

    checkVertically(i, j, N_COLS, gridCheck, currentPlayer, belowAdress);


     int aboveRight=0, aboveLeft=0;
     int *aboveRightAdress=&aboveRight, *aboveLeftAdress=&aboveLeft;

    checkDiagonal(i,j,N_COLS,gridCheck,currentPlayer, aboveRightAdress, "right");
    checkDiagonal(i,j,N_COLS,gridCheck,currentPlayer, aboveLeftAdress, "left");


    if (right+left+1>N_COLS-3 || below+1>N_COLS-3 || aboveRight>N_COLS-3 || aboveLeft>N_COLS-3) {

        printf("bravo joueur %d, vous avez win\n", currentPlayer);
        test= true;

    } else {
        test= false;
    }
    return test;
}

/**
   Cette fonction va d'une part compter sur la droite le nombre de pion identique de la valeur ajoutée dans addValue
   (currentPlayer). Si elle rencontre une valeur différente de currentPlayer, elle arrete de compter.
   Après ceci, elle se repositionne sur la valeur ajoutée et compte sur la gauche le nombre de pion identique
   à la valeur ajoutée dans addValue (même opération). La fonction checkWin va vérifier si : compteurdroit + compteurgauche > NCOLS -2

 * @param *rightAdress : pointeur qui pointe sur le compteur horizontal droit. Le compteur va être modifié
                        a chaque appel de la fonction
 * @param *leftAdress : pointeur qui pointe sur l'adresse du compteur horizontal gauche. Le compteur va être modifié
                       a chaque appel de la fonction
 */

void checkHorizontaly(int i, int j, int N_COLS, int *gridCheck, int currentPlayer, int *horizontalAdress, char direction[]) {

    int currentCell, *currentCellAdress, jCell, jCellModif, currentHorizontal=*horizontalAdress;

    if (strcmp(direction, "right")) {
        jCellModif=1;

    } else {

        jCellModif=-1;
    }

    jCell = j+jCellModif;

    currentCellAdress = gridCheck + i * N_COLS + jCell;
    currentCell = *(currentCellAdress);


    while (currentCell == currentPlayer && -1 <jCell < N_COLS+1) {

        currentHorizontal = currentHorizontal + 1;
        jCell = jCell + jCellModif;

        currentCellAdress = gridCheck + i * N_COLS + jCell;
        currentCell = *(currentCellAdress);
    }

    *horizontalAdress = currentHorizontal;
}

/**
 * Fonction qui modifie le compteur below qui permet de savoir le nombre de jeton identique
   en dessous du dernier jeton ajouté. La fonction checkWin va vérifier si : compteur_bas > NCOLS -2
 * @param belowAdress : pointeur qui pointe sur le compteur vertical du bas (below). Le compteur va être modifié
                        a chaque appel de la fonction.
 */

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
/**
 *
 * @param aboveAdress
 * @param direction
 */
 void checkDiagonal(int i,int j,int N_COLS,int *gridCheck,int currentPlayer, int *aboveAdress, char direction[]) {

    int iCell=i, jCell=j, currentCell, *currentCellAdress, currentAbove = *aboveAdress, jCellModif;

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
/**
 *
 * @return
 */

bool deleteAllowed(int N_COLS, int *gridCheck, int currentPlayer) {

    int i = 0, j , currentCell, *currentCellAdress, compteur=0;

    for (j = 0; j < N_COLS+1 ; j++) {

        currentCellAdress = gridCheck + i * N_COLS + j;
        currentCell = *(currentCellAdress);

        while (currentCell == 0 && i < N_COLS) {
            i = i + 1;

            currentCellAdress = gridCheck + i * N_COLS + j;
            currentCell = *(currentCellAdress);

            if (i == N_COLS) {
                compteur = compteur + 1;
            }
        }
        if (currentCell == currentPlayer) {
            compteur = compteur + 1;

        }
        i=0;
    }

    if (compteur > N_COLS - 1) {

        return false;

    } else {

        return true;
    }
}
/**
 * Fonction qui permet d'identifier un possible match nul. Si elle repère un match nul,
   elle renverra un booléen vrai qui arretera le programme.
 * @return
 */
bool isDrawGame (int N_COLS, int *grid) {

    int i = 0, j = 0, currentCell, *currentCellAdress, compteur = 0;

    currentCellAdress = grid + i * N_COLS + j;
    currentCell = *(currentCellAdress);
    printf("%d\n", N_COLS);

    for (j = 0; j < N_COLS; j++) {

        currentCellAdress = grid + i * N_COLS + j;
        currentCell = *(currentCellAdress);

        if (currentCell != 0) {

            compteur=compteur+1;
        }
    }

    if (compteur == N_COLS) {

        printf("match nul !!!");
        return true;
    } else {

        return false;
    }
}