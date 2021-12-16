//
// Created by NOsipov on 11/28/2021.
//

#include "common.h"

void initializeArduinoSerial() {
    Serial.begin(SERIAL_BAUDRATE);
}

int parseFirstInteger(Stream& stream) {
    int parsedInteger = 0;

    int byte1 = stream.read();
    int byte2 = stream.read();
    int byte3 = stream.read();
    int byte4 = stream.read();

    parsedInteger = byte4 | parsedInteger;
    parsedInteger = byte3 << 8 | parsedInteger;
    parsedInteger = byte2 << 16 | parsedInteger;
    parsedInteger = byte1 << 24 | parsedInteger;

    return parsedInteger;
}
