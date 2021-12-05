//
// Created by NOsipov on 11/28/2021.
//

#ifndef ALED_COMMON_H
#define ALED_COMMON_H

#include "Arduino.h"

#define SERIAL_BAUDRATE 9600

/**
 * Initializes Arduino Serial
 */
extern void initializeArduinoSerial();

/**
 * Gets size of a subarray until terminating symbol
 * E.g.
 *
 * <code>
 *  char symbols[3] = {'h', 'e', '\0'};
 *  char terminatingSymbol = '\0';
 * </code>
 *
 * Returned result: 2
 *
 * @param symbols           a symbols array
 * @param terminatingSymbol a terminating symbol
 *
 * @return size of a subarray
 */
extern int getSizeSubarrayUntilTerminatingSymbol(char symbols[], char terminatingSymbol);

extern void copy(const char from[], char to[], int startIndex, int endIndex);

#endif //ALED_COMMON_H
