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
 * Tries to parse an integer from stream <br>
 *
 * It takes first 4 bytes, decodes them into integer
 * and returns it
 *
 * @param stream a stream from integer should be parsed
 * @return a parsed integer
 */
extern int parseFirstInteger(Stream& stream);

#endif //ALED_COMMON_H
