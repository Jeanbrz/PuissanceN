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

    int answer, gameMode;

    FILE* lastGame;

    answer = displayMenu();

    switch (answer) {

        case 1 : //Chargement de la dernière partie enregistrée si elle existe

            lastGame = fopen("saveLastGame.txt", "r");

            if (lastGame != NULL){

                //Il existe une partie enregistrée, on récupère la valeur gameMode pour lancer playGame
                loadVariables(11, lastGame, &gameMode);
                fclose(lastGame);
                playGame(gameMode, false, lastGame);
            }else{

                //Il n'existe pas de partie enregistrée, on en lance une nouvelle
                printf("\nAucune ancienne partie enregistr%ce", 130);
                gameMode = getPlayerNumber();
                playGame(gameMode, true, lastGame);
            }
             break;

        case 2 : //Lancement d'une nouvelle partie

            gameMode = getPlayerNumber();
            playGame(gameMode, true, lastGame);

             break;

        case 3 : //Fermeture du programme

            printf("\nA bient%ct pour de nouvelle avantures %c! \n", 147, 2);

            return 0;

    }
}


void playGame(int gameMode, bool isNewGame, FILE* lastGame){

    bool isGameOver = false, isDraw = false;
    int N, N_COLS, cellWidth, currentPlayer, turn = 0, jNotAllowed = -1;
    int *jNotAllowedAdress = & jNotAllowed;

    long position;

    if (isNewGame == true){

        N = getTokenNumber();
        currentPlayer = getFirstPlayer();

        // On crée une variable pour stocker le nombre de colonnes/lignes, désormais on utilisera uniquement elle
        N_COLS = N + 2;
    } else {

        lastGame = fopen("saveLastGame.txt", "r");
        loadVariables(23, lastGame, &N_COLS);
    }

    // On crée un tableau d'entiers de dim N+2*N+2 qui représentera l'état de la grille
    int gridStatus[N_COLS][N_COLS];

    // On crée un pointeur sur le premier élémént du tableau
    int *gridAdress = &gridStatus[0][0];

    if (isNewGame == true){

        //Initailisation à 0 des cases de gridStatus
        initDataTable(N_COLS, gridAdress);
    } else {

        //On recrée l'état de gridStatus enregistré :
        loadDataTable(N_COLS, gridAdress, lastGame);

        //Récupération de CurrentPlayer :
        loadVariables(ftell(lastGame)+18, lastGame, &currentPlayer);

        //Récupération de Turn :
        loadVariables(ftell(lastGame)+9, lastGame, &turn);
        turn = turn - 1;
        fclose(lastGame);
    }

    //On définit la taille qu'auront les cellules de la grille en fonction de la taille des numéros de colonnes
    // qui devront êtres affichés
    //getCellWidth
    cellWidth = 2;

    // Cas où c'est à un humain de jouer
    if (gameMode == 2 || currentPlayer == 1){
        displayGrid(N_COLS, gridAdress, cellWidth, turn);
    }
    printf("\n");

    while(!isGameOver && !isDraw){
        turn = turn + 1;
        isGameOver = play(currentPlayer, N_COLS, gridAdress, turn, gameMode, jNotAllowedAdress);
        isDraw = isDrawGame(N_COLS, gridAdress);
        currentPlayer = getNextPlayer(currentPlayer);
    }

    if (replay()==1){
        initUserInterface();
    } else {
        printf("A bient%ct pour de nouvelles avanture", 147);
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

    itoa(N, NChar, 10);
    printf("NCHAR : %s", NChar);
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





