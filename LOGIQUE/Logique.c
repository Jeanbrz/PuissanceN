#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../AFFICHAGE/Affichage.h"
#include "../AFFICHAGE/userInput.h"
#include "Logique.h"
#include "../UTILS/Utils.h"

/**
 * Fonction qui permet de gerer le bloc logique en appelant toutes les autres fonctions (addValue, remove_token, Check, gameChoice, columnChoice).
 * @param N_COLS
 * @param currentPlayer
 * @param turn
 * @param gameMode
 * @return
 */
bool play(int currentPlayer, int N_COLS, int **grid, int turn, int gameMode, int *jNotAllowed) {

    int j, choice;
    bool isGameOver = false, isDeleteAllowed = true;

    FILE* lastGame;

    if (gameMode == 1 && currentPlayer == 2) {

        printf("\nOrdinateur : ");

    } else {

        if (currentPlayer==1){

            color(12,0);
            printf("Joueur %d %c vous de jouer\n", currentPlayer, 133);
            color (15,0);

        } else {

            color(14,0);
            printf("Joueur %d %c vous de jouer\n", currentPlayer, 133);
            color (15,0);
        }
    }
    
    isDeleteAllowed = deleteAllowed(N_COLS, grid, currentPlayer);
    choice = gameChoice(gameMode, currentPlayer, isDeleteAllowed);

    switch (choice) {

        case 1: //le joueur veut ajouter un jeton

            isGameOver = add_token(N_COLS, grid, currentPlayer, gameMode, jNotAllowed);
            break;

        case 2 : // le joueur veut enlever un jeton

            *jNotAllowed = remove_token(N_COLS, grid, currentPlayer, turn, gameMode);
            break;

        case 3 : //Sauvegarde des données :

            lastGame = fopen("saveLastGame.txt", "w");
            fprintf(lastGame, "N_COLS : %d\n", N_COLS);
            fprintf(lastGame, "gameMode : %d\n", gameMode);
            fprintf(lastGame, "currentPlayer : %d\n", currentPlayer);
            fprintf(lastGame, "turn : %d\n", turn);
            fputs("gridStatus : ", lastGame);

            for (int i=0; i<N_COLS; i++) {

                for (j=0; j<N_COLS; j++){

                    int currentCell = *(grid[i] + j);
                    fprintf(lastGame, "%d ", currentCell);
                }
            }
            fclose(lastGame);

            // on sort de la boucle while dans affichage.c
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
bool add_token(int N_COLS, int **gridToUpdate, int currentPlayer, int gameMode, int *jNotAllowed) {

    int i = N_COLS - 1, currentCell, j;
    bool isWin;

    j = columnChoice(N_COLS, gameMode, currentPlayer);
    currentCell = *(gridToUpdate[i]+j);

    // tant que currentCell est égale à 1 ou 2, on repète.
    while (currentCell != 0 || j==*jNotAllowed) {

        // cas où la colonne est pleine
        if ((i == 0 && currentCell != 0) || j==*jNotAllowed) {

            if(gameMode==2 || currentPlayer==1){

                printf("ERREUR - Veuillez resaisir une colonne\n");
            }

            j = columnChoice(N_COLS, gameMode, currentPlayer);
            i =  N_COLS;
        }

        i = i - 1;
        currentCell = *(gridToUpdate[i]+j);
    }

    // on donne la valeur de currentPlayer à la case du tableau
    *(gridToUpdate[i]+j) = currentPlayer;

    // on vérifie une possible victoire
    isWin = check_winner(i, j, N_COLS, gridToUpdate, currentPlayer);
    *jNotAllowed = -1;

    return isWin;
}

/**
 * Dans cette fonction on enlève le pion de l'adversaire le plus haut dans la colonne choisie par le joueur actuel.
 * @param gridToUpDown : tableau du jeu où une valeur sera supprimée
 * @return
 */
int remove_token(int N_COLS, int **gridToUpDown, int currentPlayer, int turn, int gameMode) {

    int i = 0, currentCell, j;
    j = columnChoice(N_COLS, gameMode, currentPlayer);

    currentCell = *(gridToUpDown[i]+j);

    while (currentCell!=getNextPlayer(currentPlayer)) {

        while (currentCell == 0) {

            // cas où la colonne est vide
            if (i == N_COLS-1 ) {

                if(gameMode==2 || currentPlayer == 1) {

                    printf("Veuillez resaisir une colonne\n");
                }

                j = columnChoice(N_COLS, gameMode, currentPlayer);
                i = -1;
            }

            i = i + 1;
            currentCell = *(gridToUpDown[i]+j);
        }

        if (currentCell == currentPlayer) {

            if(gameMode==2 || currentPlayer == 1) {

                printf("Vous ne pouvez pas enlever votre propre jeton, veuillez resaisir une colonne valable\n");
            }

            j = columnChoice(N_COLS, gameMode,currentPlayer);
            i=0;
        }

        currentCell = *(gridToUpDown[i]+j);
    }

    //la valeur de la case du tableau prend la valeur 0
    *(gridToUpDown[i]+j) = 0;

return j;

}

/**
 * Fonction booléenne qui appelle toutes les fonctions de Check (horizontale, verticale, diagonale)
   et qui verifie si le joueur a gagné (enchainement de N_COLS-2 même jetons). Si une des conditions de
   Check prouve que le joueur a gagné, la fonction renvoit 'true' pour arreter le programme.
 */
bool check_winner (int i, int j, int N_COLS, int **gridCheck, int currentPlayer) {

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

    // condition de victoire
    if (right+left+1>=N_COLS-2 || below>=N_COLS-2 || aboveRight>=N_COLS-2 || aboveLeft>=N_COLS-2) {

        color(15,5);
        printf("\nBravo joueur %d, vous avez gagn%c !!\n", currentPlayer, 130);
        color(15,0);
        test= true;

    } else {

        test= false;
    }

    return test;
}

/**
 * Cette fonction va d'une part compter horizontalement le nombre de jetons identique de la valeur ajoutée dans addValue
   (currentPlayer).

 * @param *rightAdress : pointeur qui pointe sur le compteur horizontal droit.
 * @param *leftAdress : pointeur qui pointe sur l'adresse du compteur horizontal gauche.
 */
void checkHorizontaly(int i, int j, int N_COLS, int **gridCheck, int currentPlayer, int *horizontalAdress, char direction[]) {

    int currentCell, jCell, jCellModif, currentHorizontal=*horizontalAdress;

    // pour savoir si le programme fait l'horizontale droite ou gauche
    if (strcmp(direction, "right")==0) {

        jCellModif=1;

    } else {

        jCellModif=-1;
    }

    jCell = j+jCellModif;
    currentCell = *(gridCheck[i]+jCell);

    // on compte le nbr de cases égales à currentPlayer
    while (currentCell == currentPlayer && -1 <jCell < N_COLS) {

        currentHorizontal = currentHorizontal + 1;
        // on se décale d'une colonne
        jCell = jCell + jCellModif;
        currentCell = *(gridCheck[i]+jCell);
    }

    *horizontalAdress = currentHorizontal;
}

/**
 * Fonction qui modifie le compteur below qui permet de savoir le nombre de jeton identique
   en dessous du dernier jeton ajouté.
 * @param belowAdress : pointeur qui pointe sur le compteur vertical du bas (below).
 */
void checkVertically(int i, int j, int N_COLS, int **gridCheck, int currentPlayer, int *belowAdress) {

    int currentCell, iCell, currentBelow=*belowAdress;

    iCell=i;
    currentCell = currentPlayer;

    // tant que les cases sur la verticale sont égales à currentPlayer
    while (currentCell==currentPlayer && iCell < N_COLS-1) {

        currentBelow = currentBelow + 1;
        iCell=iCell+1;
        currentCell = *(gridCheck[iCell]+j);
    }

    if (iCell==N_COLS-1 && currentCell==currentPlayer){
        currentBelow=currentBelow+1;
    }
    *belowAdress=currentBelow;

}

/**
 * Fonction qui modifie le compteur diagonal lorqu'elle recontre (dans la diagonale), un jeton identique à currentPlayer.
   On appelle cette fonction pour la diagonale droite et la diagonale gauche.
 * @param *aboveAdress : pointeur qui pointe sur la valeur de la diagonale droite puis sur la diagonale gauche.
 * @param direction[] : Le programme repère si on se trouve sur la diagonale droite ou gauche.
 */
 void checkDiagonal(int i,int j,int N_COLS,int **gridCheck,int currentPlayer, int *aboveAdress, char direction[]) {

    int iCell=i, jCell=j, currentCell, currentAbove = *aboveAdress, jCellModif;

        // pour savoir si le programme fait le check sur la diagonale droite ou gauche
        if (strcmp(direction, "right")==0) {

            jCellModif=1;

        } else {

            jCellModif=-1;
        }

        // On force le programme à se placer sur la case la plus basse dans la diago
        while (iCell!=N_COLS-1 && jCell>=0 && jCell<=N_COLS-1) {

            iCell=iCell+1;
            jCell=jCell-jCellModif;
        }

        currentCell = *(gridCheck[iCell]+jCell);

        // tant que le programme ne repère pas de puissance N et qu'on reste dans le tableau
        while (currentAbove<N_COLS-2 && iCell>0 && 0<jCell<N_COLS-1) {

            if (currentCell==currentPlayer) {
                // on incrémente compteur diago
                currentAbove = currentAbove + 1;

            } else {
                // on repart de zéro
                currentAbove = 0;
            }

            // on passe à la case suivante
            iCell=iCell-1;
            jCell=jCell+jCellModif;

            currentCell = *(gridCheck[iCell]+jCell);
        }

    *aboveAdress = currentAbove;
}

/** fonction booléenne qui vérifie si le joueur peut enlever une colonne. Ici, on parcourt chaque colonne, et on alimente
 un compteur si le programme repère une colonne vide ou une colonne avec la case la plus haute (dans le grille) égale à currentPlayer.
 Si le compteur est égal à N_COLS, le programme renvoit false et l'utilisateur ne pourra pas enlever de colonne.
 * @return
 */
bool deleteAllowed(int N_COLS, int **gridCheck, int currentPlayer) {

    int i = 0, j, currentCell, compteur = 0;

    // on vérifie colonne par colonne
    for (j = 0; j < N_COLS ; j++) {

        currentCell = *(gridCheck[i]+j);
        
        while (currentCell == 0 && i < N_COLS) {
            
            i = i + 1;
            
            if (i == N_COLS) {

                compteur = compteur + 1;

            } else {

                currentCell = *(gridCheck[i]+j);
            }
        }

        if (currentCell == currentPlayer) {

            // le joueur ne peut pas enlever son propre jeton
            compteur = compteur + 1;
        }

        i=0;
    }

    // si on repère que dans chaque colonne on ne peut pas enlever de jeton
    if (compteur > N_COLS - 1) {

        return false;

    } else {

        return true;
    }
}

/**
 * Fonction qui permet d'identifier un possible match nul entre les 2 joueurs. Si il ya match nul, elle renverra un booléen vrai qui arretera le programme.
 * @return
 */
bool isDrawGame (int N_COLS, int **grid) {

    int i = 0, j, currentCell, compteur = 0;

    // on vérifie colonne par colonne si elles sont pleines
    for (j = 0; j < N_COLS; j++) {

        currentCell = *(grid[i]+j);

        if (currentCell != 0) {

            compteur=compteur+1;
        }
    }

    // si on repère que tous les sommets des colonnes ont des valeurs différentes de 0
    if (compteur == N_COLS) {

        printf("match nul !!!");
        return true;

    } else {

        return false;
    }
}
