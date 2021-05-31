//
// Created by jeanb on 11/05/2021.
//

#include "Base_Donnee.h"
#include "../LOGIQUE/Logique.h"
#include "../AFFICHAGE/Affichage.h"
#include "../UTILS/Utils.h"
/**
 *
 * @param N
 * @return
 */
int initDataTable(int N_COLS, int *table_donnees){
    int i, j;
    for(i=0; i < N_COLS; i++){
        for(j=0; j < N_COLS ; j++) {
            // Si on est par exemple à la 4e ligne et 2e colonne,
            // l'adresse de la cellule est égal à :
            // table_donnees + 4 * 6 + 2
            int *currentCellAdress = table_donnees + i * (N_COLS) + j;
            *(currentCellAdress) = 0;
        }
    }

    return 0;
}


void loadDataTable (int N_COLS, int* table_donnees, FILE* lastGame){

    int i, j, cellValue=0, position;

    position = ftell(lastGame);
    position = position + 15;

    for(i=0; i < N_COLS; i++){
        for(j=0; j < N_COLS ; j++) {

            fseek(lastGame, position, SEEK_SET);
            fscanf(lastGame, "%d", &cellValue);
            position = ftell(lastGame);

            // Si on est par exemple à la 4e ligne et 2e colonne,
            // l'adresse de la cellule est égal à :
            // table_donnees + 4 * 6 + 2
            int *currentCellAdress = table_donnees + i * (N_COLS) + j;
            *(currentCellAdress) = cellValue;

        }
    }
}


void loadVariables(int position, FILE* lastGame, int * variable){

    //On place le curseur juste devant la valeur de la variable dans le fichier :
    fseek(lastGame, position, SEEK_SET);

    //On récupère la valeur souhaitée :
    fscanf(lastGame, "%d", variable);

}
