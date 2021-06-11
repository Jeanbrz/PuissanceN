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

/**
 *
 * @return
 */
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

/**
 *
 * @param isNewGame
 */
void playGame(bool isNewGame) {

    int N_COLS = 5, currentPlayer, turn = 0, jNotAllowed = -1, gameMode, i = 0, j = 0;
    int *jNotAllowedAdress = &jNotAllowed;
    bool isGameOver = false, isDraw = false;

    int **gridStatus;

    FILE *lastGame;
    lastGame = fopen("saveLastGame.txt", "r");

    //On récupère la valeur de N+2 pour dimensionner la grille
    if (isNewGame == true) {

        printf("\nSaisir le nombre de jetons\n");
        scanf("%d", &N_COLS);

        while (N_COLS<3 || N_COLS > 27){

            printf("ERREUR - Saisir le nombre de jetons (2<N<28)\n");
            scanf("%d", &N_COLS);
        }

        N_COLS=N_COLS+2;

    } else {

        loadVariables(9,lastGame,&N_COLS);
    }

    // On crée un tableau d'entiers de dim N+2 * N+2 qui représentera l'état de la grille
    gridStatus = malloc(N_COLS * sizeof(int *));
    for (i = 0; i < N_COLS; i++){

       gridStatus[i] = malloc(N_COLS * sizeof(int));
    }

    //On demande ou on charge les valeurs des varriables de jeu :
    if (isNewGame == true){

        gameMode = getPlayerNumber();
        currentPlayer = getFirstPlayer();
        initDataTable(N_COLS, gridStatus);

    } else { //On récupère toutes les données du fichier les unes apès les autres

        //On récupère lastGame :
        loadVariables(ftell(lastGame)+13, lastGame, &gameMode);
        //Récupération de CurrentPlayer :
        loadVariables(ftell(lastGame)+18, lastGame, &currentPlayer);
        //Récupération de Turn :
        loadVariables(ftell(lastGame)+9, lastGame, &turn);
        turn = turn-1;
        //On recrée l'état de gridStatus enregistré :
        loadDataTable(N_COLS, gridStatus, lastGame);
    }
    fclose(lastGame);

    //On rentre dans une boucle qui permet de joueur tant qu'une issues n'est pas validée
    while(!isGameOver && !isDraw){

        turn = turn + 1;
        show_grid(N_COLS, gridStatus, turn);
        isGameOver = play(currentPlayer, N_COLS, gridStatus, turn, gameMode, jNotAllowedAdress);
        isDraw = isDrawGame(N_COLS, gridStatus);
        currentPlayer = getNextPlayer(currentPlayer);
    }

    show_grid(N_COLS, gridStatus, turn);

    //On libère la mémoir que l'on a allouée précédement :
    free(gridStatus);

    if (replay()==1){

        initUserInterface();

    } else {

        printf("A bient%ct pour de nouvelles aventures", 147);
    }
}

/**
 * Affiche la grille de jeu
 * @param N_COLS
 * @param grid Tableau de donnée qui est traduit par la fonction
 * @param turn
 */
void show_grid(int N_COLS, int **grid, int turn){

    int i, j, currentCell;
    
    printf("\n Tour %d\n", turn);

    for (i=0; i < N_COLS; i++){

        for(j=0; j < N_COLS; j++){

          //On récupère la valeur numérique de la case visée dans la base de donnée
          currentCell = *(grid[i] + j);

          //On affiche le caractère souhaité en fonction de la valeur lue
          if (j == 0){
              printf("|");
          }
          printf(" ");

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

    //On affiche les numéros de colonne
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

/**
 * Tire au sort le premier joueur
 * @return
 */
int getFirstPlayer() {

    int alea = 0, player = 1;
    srand(time(NULL));
    
    printf("\n........TIRAGE AU SORT.........\n");
    printf("...............................\n");

    alea = rand()%2 + 1;
    player = alea;
    
    return player;
}

/**
 * Pemret de connaitre le joueur suivant
 * @param currentPlayer
 * @return
 */
int getNextPlayer(int currentPlayer) {

    int nextPlayer;

    if (currentPlayer == PLAYER_ONE) {
        nextPlayer = PLAYER_TWO;
    } else {
        nextPlayer = PLAYER_ONE;
    }

    return nextPlayer;
}
