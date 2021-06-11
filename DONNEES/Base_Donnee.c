#include "Base_Donnee.h"
#include "../LOGIQUE/Logique.h"
#include "../AFFICHAGE/Affichage.h"
#include "../UTILS/Utils.h"

/**
 * Initialise à 0 les case du tableau de données
 * @param N
 * @param table_donnees
 */
void initDataTable(int N, int **table_donnees){

    int i, j;

    for(i=0; i < N; i++){

        for(j=0; j < N; j++) {

            * (table_donnees[i]+j) = 0;
        }
    }
}

/**
 * Récupère les valeurs du tableau de donnée de la dernière partie enregistrée
 * @param N_COLS
 * @param table_donnees
 * @param lastGame
 */
void loadDataTable (int N_COLS, int **table_donnees, FILE* lastGame){

    int i, j, cellValue=0, position;

    //Déterminer la position à laquelle le cureseur devra être dans le fichier pour lire la première donnée
    position = ftell(lastGame);
    position = position + 15;

    for(i=0; i < N_COLS; i++){

        for(j=0; j < N_COLS ; j++) {

            fseek(lastGame, position, SEEK_SET); //Positionne le curseur devant la valeur à lire
            fscanf(lastGame, "%d", &cellValue);
            position = ftell(lastGame);

            *(table_donnees[i]+j) = cellValue;
        }
    }
}

/**
 * Récupérer la valeur d'une variable enregistrée
 * @param position
 * @param lastGame
 * @param variable
 */
void loadVariables(long position, FILE* lastGame, int * variable){

    //On place le curseur juste devant la valeur de la variable dans le fichier :
    fseek(lastGame, position, SEEK_SET);

    //On récupère la valeur souhaitée :
    fscanf(lastGame, "%d", variable);
}
