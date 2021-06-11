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
 * Affiche le menu de choix
 * @return
 */
int displayMenu(){

    char menuChoice[] = "";
    bool isValid = true;

    color(12,0);
    printf("\nBienvenue au puissance N\n\n");
    color(14,0);
    printf("1 - Charger la derniere partie\n"
           "2 - Lancer une nouvelle partie\n"
           "3 - Quitter\n");
    color(12,0);
    printf("\nQue voulez vous faire :");
    color(15,0);
    scanf("%s", menuChoice);

    //Vérrification du caractère numérique et de la cohérence de la saisie :
    isValid = isNumeric(menuChoice);
    if (atoi(menuChoice) < 1 || atoi(menuChoice) > 3){

        isValid = false;
    }
    while(isValid != true){

        printf("\nERREUR - Bienvenue au puissance N\n\n"
               "1 - Charger la derniere partie\n"
               "2 - Lancer une nouvelle partie\n"
               "3 - Quitter\n"
               "Que voulez vous faire :");

        scanf("%s", menuChoice);
        isValid = isNumeric(menuChoice);
        if (atoi(menuChoice) < 1 || atoi(menuChoice) > 3){

            isValid =false;
        }
    }

    return atoi(menuChoice);
}

/**
 * Connaitre le nombre de joueurs
 * @return
 */
int getPlayerNumber(){

    char playerNumber[]="1";
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

/**
 * Connaître le choix du joueur concernant l'action de jeu
 * @param gameMode
 * @param currentPlayer
 * @param deleteAllowed
 * @return
 */
int gameChoice(int gameMode, int currentPlayer, bool deleteAllowed){

    char choice[]="";
    int intChoice;
    bool isValid;
    srand(time(0));

    if(gameMode == 1 && currentPlayer == 2){

        //Cas où c'est à l'ordinateur de jouer :
        if (deleteAllowed==false){

            intChoice = 1;

        } else {

            intChoice = rand()%2+1;
        }

    } else {

        if (deleteAllowed==false){

            //Cas où c'est à un humain de joueur et que la suppression de jeton n'est pas possible
            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jeton\n"
                   "3 : Sauvegarder\n");
            scanf("%s", choice);

            //Vérification de la saisie
            intChoice = atoi(choice);
            isValid = isNumeric(choice);
            if (intChoice<1 || intChoice>3 || intChoice ==2 ) {

                isValid = false;
            }
            while(isValid!=true){

                printf("ERREUR - Que voulez-vous faire ?\n"
                       "1 : Poser un jeton\n"
                       "3 : Sauvegarder\n");
                scanf("%s", choice);
                intChoice = atoi(choice);
                isValid = isNumeric(choice);
                if (intChoice<1 || intChoice>3 || intChoice ==2 ) {

                    isValid = false;
                }
            }

        }else {

            //Humain qui joue et suppression possible :
            printf("Que voulez-vous faire ?\n"
                   "1 : Poser un jeton\n"
                   "2 : Enlever un jeton\n"
                   "3 : Sauvegarder\n");
            scanf("%s", choice);

            //Vérification de la saisie :
            intChoice = atoi(choice);
            isValid = isNumeric(choice);
            if (intChoice<1 || intChoice>3){

                isValid = false;
            }
            while(isValid!=true){

                printf("ERREUR - Que voulez-vous faire ?\n"
                       "1 : Poser un jeton\n"
                       "2 : Enlever un jeton\n"
                       "3 : Sauvegarder\n");
                scanf("%s", choice);
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

/**
 * Connaître le choix de la colonne dans laquelle le joueur veut poser un jeton
 */
int columnChoice(int N_COLS, int gameMode, int currentPlayer) {

    int rep;
    srand(time(0));

    if (gameMode == 1 && currentPlayer == 2){

        //Ordinateur qui joue
        rep = rand()%N_COLS+1;

    } else {

        //Humain qui joue
        printf("Dans quelle colonne voulez vous jouer ?\n");
        scanf("%d", &rep);

        while (rep <= 0 || rep > (N_COLS)) {

            printf("ERREUR - Veuillez saisir une valeur comprise entre 1 et %d \n", N_COLS);
            scanf("%d", &rep);
        }
    }
    rep = rep-1;

    return rep;
}

/**
 * Connaître si le joueur souhaite rejouer
 * @return
 */
int replay(){

    char answer[] = "";
    int answerInt;
    bool isValid;

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
