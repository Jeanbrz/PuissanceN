#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "Utils.h"

bool isNumeric(char *input){
    int i = 0, inputLength = strlen(input);
    bool isNumeric = true;

    while (isNumeric == true && i < inputLength) {
        char currentChar = input[i];
        if (!isdigit(currentChar)) {
            isNumeric = false;
        }

        i = i + 1;
    }

    return isNumeric;
}
