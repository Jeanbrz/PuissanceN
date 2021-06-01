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

int getTokenNumber(bool isNewGame, FILE * lastGame){

    char tokenNumber[] = "";
    int N_COLS;
    bool isValid;

    if (isNewGame == true){

        //Saisie du nombre de jettons :
        printf("\nSaisir le nombre de jetons pour jouer :\n");
        scanf("%s", tokenNumber);

        //Vérifications de la saisie :
        isValid = isNumeric(tokenNumber);
        N_COLS = atoi(tokenNumber);
        if(N_COLS<3){
            isValid = false;
        }
        while(isValid!=true){
            printf("ERREUR - Saisir le nombre de jetons (>2) ?\n");
            scanf("%s", tokenNumber);
            isValid = isNumeric(tokenNumber);
            N_COLS = atoi(tokenNumber);
            if(N_COLS<3){
                isValid = false;
            }
        }
        // On crée une variable pour stocker le nombre de colonnes/lignes, désormais on utilisera uniquement elle
        N_COLS = N_COLS+2;

    } else {

        loadVariables(9, lastGame, &N_COLS);

    }

    return N_COLS;
}

int gameChoice(int gameMode, int currentPlayer, bool deleteAllowed){

    char choice[]="";
    int intChoice;
    bool isValid;
    srand(time(0));

    if(gameMode == 1 && currentPlayer == 2){

        if (deleteAllowed==false){
            intChoice = 1;
        } else {
            intChoice = rand()%2+1;
        }
        printf("Choix machine : %d\n", intChoice);
    } else {

        if (deleteAllowed==false){
            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jetton\n"
                   "3 : Sauvegarder\n");
            scanf("%s", choice);

            //Verrification de la saisie
            intChoice = atoi(choice);
            isValid = isNumeric(choice);
            if (intChoice<1 || intChoice>3 || intChoice ==2 ) {
                isValid = false;
            }
            while(isValid!=true){
                printf("ERREUR - Que voulez-vous faire ?\n"
                       "1 : Poser un jetton\n"
                       "3 : Sauvegarder\n");
                scanf("%s", choice);

                intChoice = atoi(choice);
                isValid = isNumeric(choice);
                if (intChoice<1 || intChoice>3 || intChoice ==2 ) {
                    isValid = false;
                }
            }
        }else {

            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jetton\n"
                   "2 : Enlever un jetton\n"
                   "3 : Sauvegarder\n");
            scanf("%s", choice);

            //Vérifications de la saisie :
            intChoice = atoi(choice);
            isValid = isNumeric(choice);
            if (intChoice<1 || intChoice>3){
                isValid = false;
            }

            while(isValid!=true){
                printf("Que voulez-vous faire ?\n"
                       "1 : Poser un jetton\n"
                       "2 : Enlever un jetton\n"
                       "3 : Sauvegarder\n");
                scanf("%s", choice);

                //Vérifications de la saisie :
                intChoice = atoi(choice);
                isValid = isNumeric(choice);
                if (intChoice<1 || intChoice>3){
                    isValid = false;
                }
            }
        }
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

        while (rep <= 0 || rep > (N_COLS)) {
            printf("Veuillez saisir une valeur comprise entre 1 et %d \n", N_COLS);
            scanf("%d", &rep);
        }
    }

    rep = rep-1;
    return rep;
}

int replay(){

    char answer[] = "";
    int answerInt;
    bool isValid;

    //Saisie du nombre de jettons :
    printf("\nVoulez-vous rejouer ? \n"
           "1 : Oui\n"
           "2 : Non\n");
    scanf("%s", answer);

    //Vérifications de la saisie :
    isValid = isNumeric(answer);
    answerInt = atoi(answer);
    if(answerInt<1 || answerInt>2){
        isValid = false;
    }
    while(isValid!=true){
        printf("\nERREUR - Voulez-vous rejouer ? \n"
               "1 : Oui\n"
               "2 : Non\n");
        scanf("%s", answer);

        isValid = isNumeric(answer);
        answerInt = atoi(answer);
        if(answerInt<1 || answerInt>2){
            isValid = false;
        }
    }
    return answerInt;


}
