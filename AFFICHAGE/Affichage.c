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
#include "userInput.h"

#define PLAYER_ONE 1
#define PLAYER_TWO 2


int initUserInterface(){

    int answer, playerNumber, gameMode;

    FILE* lastGame = fopen("saveLastGame.txt", "r");

    answer = displayMenu();

    switch (answer) {

        case 1 :

            if (lastGame != NULL){
                fseek(lastGame, 11, SEEK_SET);
                fscanf(lastGame, "%d", &gameMode);
                fclose(lastGame);
                printf("game mode : %d\n", gameMode);
                playGame(gameMode, false);
            }else{
                printf("\nAucune ancienne partie chargee");
                playerNumber = getPlayerNumber();
                if (playerNumber == 1){
                    gameMode = 1;
                }else{
                    gameMode = 2;
                }
                playGame(gameMode, true);
            }
             break;

        case 2 :
            playerNumber = getPlayerNumber();
            if (playerNumber == 1){
                gameMode = 1;
                playGame(gameMode, true);
            }else{
                gameMode = 2;
                playGame(gameMode, true);
            }
             break;

        case 3 : printf("\nA bientot pour de nouvelle avantures ! \n"); return 0;

    }
    return 0;
}


void playGame(int gameMode, bool isNewGame){

    bool isGameOver = false;
    int N, N_COLS, cellWidth, currentPlayer, turn = 0, jNotAllowed = -1;
    int *jNotAllowedAdress = & jNotAllowed;

    if (isNewGame == true){

        N = getTokenNumber();

        currentPlayer = getFirstPlayer();

        // On crée tout de suite une variable pour le nb de colonnes, désormais on utilisera uniquement elle
        N_COLS = N + 2;
    } else {

        FILE* lastGame = fopen("saveLastGame.txt", "r");
        fseek(lastGame, 9, 2);
        fprintf(lastGame, "%d", N_COLS);
        fclose(lastGame);

    }

    // on crée le tableau une bonne fois pour toutes en mémoire
    int gridStatus[N_COLS][N_COLS];

    // On crée un pointeur sur le premier élémént du tableau
    int *gridAdress = &gridStatus[0][0];

    if (isNewGame == true){

        //Initailisation à 0 des cases de gridStatus
        init_donnees(N_COLS, gridAdress);

    }

    //getCellWidth
    cellWidth = 2;


    if (gameMode == 2 || currentPlayer == 1){
        displayGrid(N_COLS, gridAdress, cellWidth, turn);
    }
    printf("\n");

    while(!isGameOver){
        isGameOver = play(currentPlayer, N_COLS, gridAdress, turn, gameMode, jNotAllowedAdress);
        isGameOver = isDrawGame(currentPlayer, N_COLS, gridAdress);
        currentPlayer = getNextPlayer(currentPlayer);
        turn = turn + 1;
    }
    if (replay()==1){
        initUserInterface();
    } else {
        printf("A bientôt pour de nouvelles avanture");
    }
}





void displayGrid(int N_COLS, int *grid, int cellWidth, int turn){

    int i, j, space, currentCell;

    printf("\n Tour %d\n", turn+1);
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

    printf("  ");
    for (i=0; i<N_COLS; i++){

        printf("%d", i+1);
        for (j=0; j<=cellWidth; j++){
            printf(" ");
        }
    }
    printf("\n");
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





