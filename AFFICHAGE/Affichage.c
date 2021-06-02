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

            printf("\nA bient%ct pour de nouvelle avantures %c! \n", 147, 2);

            return 0;

    }

    //Lancement d'une partie si choix 1 ou 2 avec isNewGame en paramètre définit dans le switch-case
    playGame(isNewGame);
}


void playGame(bool isNewGame){

    int N_COLS, cellWidth, currentPlayer, turn = 0, jNotAllowed = -1, gameMode;
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
        turn = turn - 1;

        //On recrée l'état de gridStatus enregistré :
        loadDataTable(N_COLS, gridAdress, lastGame);
    }
    fclose(lastGame);

    //On définit la taille qu'auront les cellules de la grille en fonction de la taille des numéros de colonnes
    // qui devront êtres affichés
    //getCellWidth
    cellWidth = 2;

    // Cas où c'est à un humain de jouer
    if (gameMode == 2 || currentPlayer == 1){
        show_grid(N_COLS, gridAdress, cellWidth, turn);
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
        printf("A bient%ct pour de nouvelles aventures", 147);
    }
}


void show_grid(int N_COLS, int *grid, int cellWidth, int turn){

    int i, j, space, currentCell;

    printf("\n Tour %d\n", turn+1);
    for (i=0; i < N_COLS; i++){

        for(j=0; j < N_COLS; j++){
            space=0;

            if (j == 0){
                printf("|");
            } else {
                printf("_");

            }

            currentCell = *(grid + i * (N_COLS) + j);
            if(currentCell == 0){
                printf("_");
            }
            if(currentCell == 1){
                printf("X");
            }
            if(currentCell == 2){
                printf("O");
            }

            //Afficher une cellule de la bonne largeure
            while(space<cellWidth-1){
                printf("_");
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





