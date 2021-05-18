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
int init_donnees(int N, int table_donnees[N+1][N+1]){

    int i, j;
    for(i=0; i<=N+1; i++){
        for(j=0; j<=N+1; j++){
            table_donnees[i][j] = 0;
        }
    }
}
