#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Affichage.h"
#include "../DONNEES/Base_Donnee.h"
#include "../LOGIQUE/Logique.h"
#include "../UTILS/Utils.h"
#include "Affichage.h"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

/**
 * Lance le jeu en affichant le menu et les procédures en fonction du choix utilisateur
 * @return
 */
int initUserInterface(){

    playGame();

    return 0;
}

/**
 * Saisie le nombre de jettons, initialise les données et la grille
 */
void playGame(){

    bool isValid = true, isGameOver = false;
    char tokenNumber[] = "";
    int N, N_COLS, cellWidth, currentPlayer;

    //Saisie du nombre de jettons :
    printf("\nSaisir le nombre de jetons pour jouer :\n");
    scanf("%c", tokenNumber);

    // J'ai forcé N à valoir 4 pour simplifier mes tests
    N = 4;

    // On crée tout de suite une variable pour le nb de colonnes, désormais on utilisera uniquement elle
    N_COLS = N + 2;

    // pareil j'ai forcé le currentPlayer
    //currentPlayer = getFirstPlayer();
    currentPlayer = 2;

    cellWidth = 2;

    // on crée le tableau une bonne fois pour toutes en mémoire
    int gridStatus[N_COLS][N_COLS];

    // On crée un pointeur sur le premier élémént du tableau
    int *gridAdress = &gridStatus[0][0];

    //Initailisation à 0 des cases de gridStatus
    init_donnees(N_COLS, gridAdress);
    displayGrid(N_COLS, gridAdress, 2);
    printf("\n");

    while(!isGameOver){
        //displayGrid(N, gridStatus, cellWidth);
        printf("\ncoucou: %d\n", N);
        isGameOver = play(currentPlayer, N_COLS, gridAdress);
        currentPlayer = getNextPlayer(currentPlayer);
    }
}

void displayGrid(int N_COLS, int *grid, int cellWidth){

    int i, j, space, currentCell;

    for (i=0; i < N_COLS; i++){

        for(j=0; j < N_COLS; j++){
            space=0;

            if (j == 0){
                printf("|");
            }

            currentCell = *(grid + i * (N_COLS) + j);
            if(currentCell == 0){
                printf(" ");
            }
            if(currentCell == 1){
                printf("X");
            }
            if(currentCell == 2){
                printf("O");
            }

            //Afficher une cellule de la bonne largeure
            while(space<cellWidth){
                printf(" ");
                space = space+1;
            }
            printf("|");
        }
        printf("\n");
    }
}


int getCellWidth(int N){

    char NChar[]="";
    int width = 0;

    sprintf(NChar, "%d", N + 2);
    if (strlen(NChar)%2 == 0){
        width = strlen(NChar)+1;
    } else {
        width = strlen(NChar);
    }
    return width;
}


int getFirstPlayer() {

    int alea = 0, player = 0;

    srand(time(NULL));

    printf("\n........TIRAGE AU SORT.........\n");
    printf("...............................\n");

    alea = rand()%2 + 1;

    printf("%s", "helli");

    if (alea == 1){
        player = PLAYER_ONE;
    } else {
        player = PLAYER_TWO;
    }

    return player;
}

int getNextPlayer(int currentPlayer) {
    int nextPlayer;

    if (currentPlayer == PLAYER_ONE) {
        nextPlayer = PLAYER_TWO;
    } else {
        nextPlayer = PLAYER_ONE;
    }

    return nextPlayer;
}





