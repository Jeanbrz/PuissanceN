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
int init_donnees(int N, int table_donnees[N + 2][N + 2]){

    int i, j;
    for(i=0; i<N+2; i++){
        for(j=0; j<N+2; j++){
            table_donnees[i][j] = 0;
        }
    }
}
