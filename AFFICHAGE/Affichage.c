#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Affichage.h"
#include "../DONNEES/Base_Donnee.h"
#include "../LOGIQUE/Logique.h"
#include "../UTILS/Utils.h"

/**
 * Lance le jeu en affichant le menu et les procédures en fonction du choix utilisateur
 * @return
 */
int initGame(){
    char menuChoice[] = "";
    bool isValid = true;

    menu();

    scanf("%s", &menuChoice);
    isValid = isNumeric(menuChoice);

    while(isValid != true){
        printf("\nERREUR\n");
        menu();
        scanf("%s", &menuChoice);
        isValid= isNumeric(menuChoice);
    }

    switch (atoi(menuChoice)) {
        case 1:
            //charger_partie;
            break;
        case 2:
            nouvelle_partie;
            break;
        case 3:
            printf("\n A bientot pour de nouvelles aventures !!!\n");
            return 0;
    }
}

/**
 * Affiche le menu d'options
 */
void menu(){
    printf("Bienvenue au puissance N\n\n"
           "1-Charger la derniere partie\n"
           "2-Lancer une nouvelle partie\n"
           "3-Quitter\n"
           "Que voulez vous faire :");
}

/**
 * Saisie le nombre de jettons, initialise les données et la grille
 */
void nouvelle_partie(){

    //Saisie du nombre de jettons :
    char nbrjettons[]="";
    int test;
    printf("Saisir le nombre de jettons pour jouer :\n");
    scanf("%s", &nbrjettons);
    //Vérifications de la saisie :
    test= isNumeric(nbrjettons);
    while(test!=0){
        printf("\nERREUR-Saisissez une valeur num%crique jouable (>=2) :\n", 130);
        scanf("%s", &nbrjettons);
        test= isNumeric(nbrjettons);
    }
 
}



int getCellWidth(int N){

    char NChar[] = "";
    int width = 0;

    itoa(N, NChar, 10);
    /*if (strlen(NLength)%2 == 0){
        width = N + 1;
    } else {
        width = N;
    }*/

    return strlen(NChar);
}
