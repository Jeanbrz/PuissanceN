#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "Utils.h"

/**
 * Permet de déterminer si une saisie est purement numérique
 * @param input
 * @return
 */
bool isNumeric(char input[]){

    int i = 0, inputLength = strlen(input);
    char currentChar;
    bool isNumeric = true;

    while (isNumeric == true && i < inputLength) {

        currentChar = input[i];

        if (!isdigit(currentChar)) {

            //Si le caractère en cours de lecture n'est pas numérique
            isNumeric = false;
        }
        i = i + 1;
    }

    return isNumeric;
}

/**
 * Fonction permettant d'intégrer des couleurs
 * @param t
 * @param f
 */
void color(int t,int f){

    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
