#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

    int answer;
    bool isNewGame;

    FILE* lastGame;

    answer = displayMenu();

    switch (answer) {

        case 1 : //On souhaite charger la dernière partie

            lastGame = fopen("saveLastGame.txt", "r");

            if (lastGame != NULL){

                //Il existe une ancienne partie chargée
                isNewGame = false;

            }else{

                //Il n'existe pas de partie enregistrée, on en lance une nouvelle
                printf("\nAucune ancienne partie enregistr%ce", 130);
                isNewGame = true;
            }
            fclose(lastGame);
             break;

        case 2 : //On souhaite lancer une nouvelle partie

            isNewGame = true;

             break;

        case 3 : //On souhaite quitter le programme

            printf("\nA bient%ct pour de nouvelle aventures %c! \n", 147, 2);

            return 0;

    }

    //Lancement d'une partie si choix 1 ou 2 avec isNewGame en paramètre définit dans le switch-case
    playGame(isNewGame);
    return 1;
}


void playGame(bool isNewGame){

    int N_COLS, currentPlayer, turn = -1, jNotAllowed = -1, gameMode;
    int *jNotAllowedAdress = & jNotAllowed;
    bool isGameOver = false, isDraw = false;

    FILE* lastGame;
    lastGame = fopen("saveLastGame.txt", "r");

    //On récupère la valeur de N+2 pour dimensionner la grille
    N_COLS = getTokenNumber(isNewGame, lastGame);

    // On crée un tableau d'entiers de dim N+2 * N+2 qui représentera l'état de la grille
    int ** gridStatus = malloc(N_COLS * sizeof(int *));
    for (int i =0; i<N_COLS; i++){
        gridStatus[i] = malloc(N_COLS * sizeof(int));
    }
    // On crée un pointeur sur le premier élément du tableau, il s'agit de l'élément de départ
    // que nous donnons à nos fonctions
    int *gridAdress = &gridStatus[0][0];

    if (isNewGame == true){

        gameMode = getPlayerNumber();
        currentPlayer = getFirstPlayer();

        //Initailisation à 0 des cases de gridStatus
        initDataTable(N_COLS, gridAdress);

    } else { //On récupère toutes les données du fichier les unes apès les autres

        //On récupère lastGame :
        loadVariables(ftell(lastGame)+13, lastGame, &gameMode);

        //Récupération de CurrentPlayer :
        loadVariables(ftell(lastGame)+18, lastGame, &currentPlayer);

        //Récupération de Turn :
        loadVariables(ftell(lastGame)+9, lastGame, &turn);

        //On recrée l'état de gridStatus enregistré :
        loadDataTable(N_COLS, gridAdress, lastGame);
    }
    fclose(lastGame);

    while(!isGameOver && !isDraw){

        turn = turn + 1;
        show_grid(N_COLS, gridAdress, turn);
        isGameOver = play(currentPlayer, N_COLS, gridAdress, turn, gameMode, jNotAllowedAdress);
        isDraw = isDrawGame(N_COLS, gridAdress);
        currentPlayer = getNextPlayer(currentPlayer);
    }
    show_grid(N_COLS, gridAdress, turn);
    free(lastGame);
    if (replay()==1){
        initUserInterface();
    } else {
        printf("A bient%ct pour de nouvelles aventures", 147);
    }
}


void show_grid(int N_COLS, int *grid, int turn){

    int i, j, currentCell;

    printf("\n Tour %d\n", turn+1);

    for (i=0; i < N_COLS; i++){

        for(j=0; j < N_COLS; j++){

            if (j == 0){
                printf("|");
            }
            printf(" ");

            currentCell = *(grid + i * (N_COLS) + j);
            if(currentCell == 0){
                printf("_");
            }
            if(currentCell == 1){
                color(12,0);
                printf("X");
                color(15,0);
            }
            if(currentCell == 2){
                color(14,0);
                printf("O");
                color(15,0);
            }

            printf(" ");
            printf("|");
        }
        printf("\n");
    }


    for (i=0; i<N_COLS; i++){

        if (i>=10){
            printf(" ");
        } else {
            printf("  ");
        }
        printf("%d", i+1);
        printf(" ");


    }
    printf("\n");
}


int getFirstPlayer() {

    int alea = 0, player = 0;

    srand(time(NULL));

    color (1,0);
    printf("\n........TIRAGE AU SORT.........\n");
    printf("...............................\n");
    color (15,0);

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





