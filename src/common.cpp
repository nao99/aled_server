//
// Created by NOsipov on 11/28/2021.
//

#include "common.h"

void initializeArduinoSerial() {
    Serial.begin(SERIAL_BAUDRATE);
}

int getSizeSubarrayUntilTerminatingSymbol(char symbols[], char terminatingSymbol) {
    size_t symbolsLength = strlen(symbols);

    int subarrayLength = 0;
    for (int i = 0; i < symbolsLength; i++) {
        if (symbols[i] == terminatingSymbol) {
            break;
        }

        subarrayLength++;
    }

    return subarrayLength;
}

void copy(const char from[], char to[], int startIndex, int endIndex) {
    int j = 0;
    for (int i = startIndex; i < endIndex; i++) {
        to[j] = from[i];
        j++;
    }
}
