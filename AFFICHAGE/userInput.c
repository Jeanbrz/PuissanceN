#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#include "Affichage.h"
#include "../DONNEES/Base_Donnee.h"
#include "../LOGIQUE/Logique.h"
#include "../UTILS/Utils.h"
#include "Affichage.h"

/**
 * Affiche le menu d'options
 */
int displayMenu(){

    char menuChoice[] = "";
    bool isValid = true;

    printf("Bienvenue au puissance N\n\n"
           "1-Charger la derniere partie\n"
           "2-Lancer une nouvelle partie\n"
           "3-Quitter\n"
           "Que voulez vous faire :");

    scanf("%s", menuChoice);

    //Vérrification du caractère numérique et de la cohérence de la saisie :
    isValid = isNumeric(menuChoice);

    if (atoi(menuChoice) < 1 || atoi(menuChoice) > 3){
        isValid = false;
    }

    while(isValid != true){
        printf("\nERREUR - Bienvenue au puissance N\n\n"
               "1-Charger la derniere partie\n"
               "2-Lancer une nouvelle partie\n"
               "3-Quitter\n"
               "Que voulez vous faire :");

        scanf("%s", menuChoice);
        isValid = isNumeric(menuChoice);

        if (atoi(menuChoice) < 1 || atoi(menuChoice) > 3){
            isValid =false;
        }
    }

    return atoi(menuChoice);
}


int getPlayerNumber(){

    char playerNumber[]="";
    bool isValid;

    printf("\nNombre de joueur (1 ou 2) : ");
    scanf("%s", playerNumber);

    //Vérrification du caractère numérique et de la cohérence de la saisie :
    isValid = isNumeric(playerNumber);
    if(atoi(playerNumber)<1 || atoi(playerNumber)>2){
        isValid = false;
    }
    while(isValid != true){
        printf("\nERREUR - Nombre de joueur (1 ou 2) : ");
        scanf("%s", playerNumber);

        isValid = isNumeric(playerNumber);
        if (atoi(playerNumber) < 1 || atoi(playerNumber) > 2){
            isValid =false;
        }
    }

    return atoi(playerNumber);
}

int gameChoice(int turn, int gameMode, int currentPlayer){

    char choice[]="";
    int intChoice;
    bool isValid;
    srand(time(0));

    if(gameMode == 1 && currentPlayer == 2){

        if (turn == 0){
            intChoice = 1;
        } else {
            intChoice = rand()%2+1;
        }
        printf("choix machine : %d\n", intChoice);
    } else {

        if (turn ==0){
            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jetton\n");
            scanf("%s", choice);

            //Vérifications de la saisie :
            isValid = isNumeric(choice);
            while(isValid!=true){
                printf("ERREUR - Que voulez-vous faire ?\n"
                       "1 : Poser un jetton\n");
                scanf("%s", choice);
                isValid = isNumeric(choice);
            }
        }else {

            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jetton\n"
                   "2 : Enlever un jetton\n");
            scanf("%s", choice);

            //Vérifications de la saisie :
            isValid = isNumeric(choice);
            while(isValid!=true){
                printf("ERREUR - Que voulez-vous faire ?\n"
                       "1 : Poser un jetton\n"
                       "2 : Enlever un jetton\n");
                scanf("%s", choice);
                isValid = isNumeric(choice);
            }
        }
        intChoice = atoi(choice);
    }

    return intChoice;
}

int columnChoice(int N_COLS, int gameMode, int currentPlayer) {

    int rep;
    srand(time(0));

    if (gameMode == 1 && currentPlayer == 2){

        rep = rand()%N_COLS+1;

    } else {

        printf("Dans quelle colonne voulez vous jouer ?\n");
        scanf("%d", &rep);

        while (rep < 0 || rep > (N_COLS)) {
            printf("veuillez saisir une valeur comprise entre 1 et %d \n", N_COLS);
            scanf("%d", &rep);
        }
    }

    rep = rep-1;
    return rep;
}


