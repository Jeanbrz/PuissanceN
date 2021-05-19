#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    scanf("%c", menuChoice);

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

        scanf("%c", menuChoice);
        isValid = isNumeric(menuChoice);

        if (atoi(menuChoice) < 1 || atoi(menuChoice) > 3){
            isValid =false;
        }
    }

    return atoi(menuChoice);
}

int columnChoice(int N_COLS) {

    int rep;

    printf("Dans quelle colonne voulez vous jouer ?\n");
    scanf("%d", &rep);

    while (rep < 0 || rep > (N_COLS)) {
        printf("veuillez saisir une valeur comprise entre 1 et %d \n", N_COLS);
        scanf("%d", &rep);
    }
    rep = rep-1;
    return rep;
}


int gameChoice(){

    char choice[]="";
    bool isValid;


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
    return atoi(choice);
}