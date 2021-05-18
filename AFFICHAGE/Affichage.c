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

    int menuChoice;

    menuChoice = displayMenu();

    //Choix de la suite du programme en fonction de la saisie :
    switch (menuChoice) {
        case 1:
            //charger_partie();
            break;
        case 2:
            playGame();
            break;
        case 3:
            printf("\n A bientot pour de nouvelles aventures\n");
            return 0;
    }
}

/**
 * Saisie le nombre de jettons, initialise les données et la grille
 */
void playGame(){
    
    bool isValid = true, isGameOver = false;
    char tokenNumber[]="";
    int N, cellWidth, currentPlayer;

    //Saisie du nombre de jettons :
    printf("\nSaisir le nombre de jettons pour jouer :\n");
    scanf("%s", &tokenNumber);

    //Vérrification du caractère numérique et de la cohérence de la saisie :
    isValid = isNumeric(tokenNumber);
    if(atoi(tokenNumber) < 2){
        isValid=false;
    }
    while(isValid!=true){
        printf("\nERREUR-Saisissez une valeur num%crique jouable (>=2) :\n", 130);
        scanf("%s", &tokenNumber);
        isValid = isNumeric(tokenNumber);
        if(atoi(tokenNumber) < 2){
            isValid=false;
        }
    }

    N = atoi(tokenNumber);
    int gridStatus[N+1][N+1];

    currentPlayer = getFirstPlayer();
    cellWidth=2;

    //Initailisation à 0 des cases de gridStatus :
    init_donnees(N, gridStatus);

    while(!isGameOver){
        displayGrid(N, gridStatus, cellWidth);
        isGameOver = play(currentPlayer, N, gridStatus);
        currentPlayer = getNextPlayer(currentPlayer);
    }
}

void displayGrid(int N, int grid[N+1][N+1], int cellWidth){

    int i, j, space;

    for (i=0; i<=N+1; i++){

        for(j=0; j<=N+1; j++){
            space=0;

            if (j == 0){
                printf("|");
            }
            if(grid[i][j]==0){
                printf(" ");
            }
            if(grid[i][j]==1){
                printf("X");
            }
            if(grid[i][j]==2){
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

    itoa(N+2, NChar, 10);
    if (strlen(NChar)%2 == 0){
        width = strlen(NChar)+1;
    } else {
        width = strlen(NChar);
    }
    return width;
}


int getFirstPlayer() {

    int alea, player;
    srand(time(0));

    printf("\n........TIRAGE AU SORT.........\n");
    printf("...............................\n");
    alea = rand()%2+1;
    if (alea==1){
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


