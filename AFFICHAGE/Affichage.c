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

    char menuChoice[] = "";
    bool isValid = true;

    displayMenu();
    scanf("%s", &menuChoice);
    isValid = isNumeric(menuChoice);
    while(isValid != true){
        isValid = true;
        printf("\nERREUR\n");
        displayMenu();
        scanf("%s", &menuChoice);
        isValid = isNumeric(menuChoice);
    }

    switch (atoi(menuChoice)) {
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
 * Affiche le menu d'options
 */
void displayMenu(){
    printf("Bienvenue au puissance N\n\n"
           "1-Charger la derniere partie\n"
           "2-Lancer une nouvelle partie\n"
           "3-Quitter\n"
           "Que voulez vous faire :");
}

/**
 * Saisie le nombre de jettons, initialise les données et la grille
 */
void playGame(){

    //Saisie du nombre de jettons :
    char nbrjettons[]="";
    bool isValid = true, isGameOver = false;
    int N, cellWidth;
    int currentPlayer;

    printf("\nSaisir le nombre de jettons pour jouer :\n");
    scanf("%s", &nbrjettons);
    //Vérifications de la saisie :
    isValid = isNumeric(nbrjettons);
    if(atoi(nbrjettons)<2){
        isValid=false;
    }
    while(isValid!=true){
        printf("\nERREUR-Saisissez une valeur num%crique jouable (>=2) :\n", 130);
        scanf("%s", &nbrjettons);
        isValid = isNumeric(nbrjettons);
        if(atoi(nbrjettons)<2){
            isValid=false;
        }
    }

    N=atoi(nbrjettons);
    int gridStatus[N+2][N+2];
    currentPlayer = getFirstPlayer();
    cellWidth = getCellWidth(N);
    // Mise à 0 de gridStatus :
    init_donnees(N, gridStatus);
    while(!isGameOver){
        displayGrid(N, gridStatus, cellWidth);
        isGameOver = play(currentPlayer, N, gridStatus);
        currentPlayer = getNextPlayer(currentPlayer);
    }
}

void displayGrid(int N, int grid[N+2][N+2], int cellWidth){

    int i, j, space;

    for (i=0; i<N+2; i++){
        space=0;

        for(j=0; j<N+2; j++){

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

            //Afficher une cellule de la bonn,e largeure
            while(space<cellWidth-1){
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
    printf("\n%s\n", NChar);
    if (strlen(NChar)%2 == 0){
        width = strlen(NChar)+1;
    } else {
        width = strlen(NChar);
    }
    printf("\n%d\n", width);
    return width;
}


int columnChoice(int N) {

    int rep;

    printf("Dans quelle colonne voulez vous jouer ?\n");
    scanf("%d", &rep);

    while (rep<0 || rep>N+2) {
        printf("veuillez saisir une valeur comprise entre 1 et %d \n", N+2);
        scanf("%d", &rep);
    }
    rep = rep-1;
    return rep;
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


int gameChoice(){

    char choice[]="";
    bool isValid;


    printf("Que voulez-vous faire ?\n"
           "1 : Poser un jetton\n"
           "2 : Enlever un jetton\n");
    scanf("%s", &choice);

    //Vérifications de la saisie :
    isValid = isNumeric(choice);
    while(isValid!=true){
        printf("ERREUR - Que voulez-vous faire ?\n"
               "1 : Poser un jetton\n"
               "2 : Enlever un jetton\n");
        scanf("%d", &choice);
        isValid = isNumeric(choice);
    }
    return atoi(choice);
}