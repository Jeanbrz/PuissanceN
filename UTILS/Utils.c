#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "Utils.h"

bool isNumeric(char *input){
    int i = 0, inputLength = strlen(input);
    char currentChar;
    bool isNumeric = true;

    while (isNumeric == true && i < inputLength) {
        currentChar = input[i];
        if (!isdigit(currentChar)) {
            isNumeric = false;
        }
        i = i + 1;
    }

    return isNumeric;
}
